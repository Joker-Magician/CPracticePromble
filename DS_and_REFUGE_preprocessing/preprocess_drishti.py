import cv2
import numpy as np
import os
import glob
from tqdm import tqdm

# --- 1. 定义常量 ---
PROJECT_ROOT = '.' 

# 原始 Drishti-GS 数据集在服务器上的路径
DS_ROOT = os.path.join(PROJECT_ROOT, 'data/drishtigs')
DS_TRAIN_PATH = os.path.join(DS_ROOT, 'Training-20211018T055246Z-001/Training')
DS_TEST_PATH = os.path.join(DS_ROOT, 'Test-20211018T060000Z-001/Test')

# --- 新：定义两个独立的输出目录 ---
OUTPUT_DIR_TRAIN = os.path.join(PROJECT_ROOT, 'data/Drishti-GS_preprocessed_Train')
OUTPUT_IMG_DIR_TRAIN = os.path.join(OUTPUT_DIR_TRAIN, 'images')
OUTPUT_MASK_DIR_TRAIN = os.path.join(OUTPUT_DIR_TRAIN, 'masks')

OUTPUT_DIR_TEST = os.path.join(PROJECT_ROOT, 'data/Drishti-GS_preprocessed_Test')
OUTPUT_IMG_DIR_TEST = os.path.join(OUTPUT_DIR_TEST, 'images')
OUTPUT_MASK_DIR_TEST = os.path.join(OUTPUT_DIR_TEST, 'masks')

# 论文中提到的最终尺寸
TARGET_SIZE = (512, 512)
PADDING = 30 
MASK_VALS = {'cup': 255, 'disc': 128, 'bg': 0}

# --- 2. 创建所有输出目录 ---
os.makedirs(OUTPUT_IMG_DIR_TRAIN, exist_ok=True)
os.makedirs(OUTPUT_MASK_DIR_TRAIN, exist_ok=True)
os.makedirs(OUTPUT_IMG_DIR_TEST, exist_ok=True)
os.makedirs(OUTPUT_MASK_DIR_TEST, exist_ok=True)


# --- 新：函数现在接受输出路径作为参数 ---
def process_dataset(image_paths, gt_base_path, output_img_dir, output_mask_dir):
    """
    循环处理所有图像，执行“先裁剪、后缩放”
    """
    processed_count = 0
    for img_path in tqdm(image_paths):
        try:
            # --- a. 构建文件路径 ---
            img_name = os.path.basename(img_path)
            img_id = img_name.split('.')[0] 

            od_mask_path = os.path.join(gt_base_path, img_id, 'SoftMap', f'{img_id}_ODsegSoftmap.png')
            cup_mask_path = os.path.join(gt_base_path, img_id, 'SoftMap', f'{img_id}_cupsegSoftmap.png')
            
            # --- b. 读取所有文件 ---
            image = cv2.imread(img_path)
            od_mask = cv2.imread(od_mask_path, cv2.IMREAD_GRAYSCALE)
            cup_mask = cv2.imread(cup_mask_path, cv2.IMREAD_GRAYSCALE)
            
            if image is None:
                print(f"警告：读取图像失败，跳过: {img_path}")
                continue
            if od_mask is None:
                print(f"警告：读取OD掩码失败，跳过: {od_mask_path}")
                continue
            if cup_mask is None:
                print(f"警告：读取Cup掩码失败，跳过: {cup_mask_path}")
                continue
                
            h, w = od_mask.shape[:2]

            # --- c. 定位：从 OD 掩码计算边界框 ---
            y_indices, x_indices = np.nonzero(od_mask)
            
            if len(y_indices) == 0:
                print(f"警告：OD掩码 {img_id} 为空，跳过。")
                continue
            
            x_min = np.min(x_indices)
            x_max = np.max(x_indices)
            y_min = np.min(y_indices)
            y_max = np.max(y_indices)
            
            # --- d. 应用安全边距 (Padding) ---
            x_min = max(0, x_min - PADDING)
            y_min = max(0, y_min - PADDING)
            x_max = min(w, x_max + PADDING)
            y_max = min(h, y_max + PADDING)
            
            # --- e. 创建新的、正确的组合掩码 ---
            new_mask = np.full((h, w), MASK_VALS['bg'], dtype=np.uint8)
            new_mask[od_mask > 128] = MASK_VALS['disc']
            new_mask[cup_mask > 128] = MASK_VALS['cup']
            
            # --- f. 裁剪：从原始图像和新掩码中裁剪出ROI ---
            cropped_image = image[y_min:y_max, x_min:x_max]
            cropped_mask = new_mask[y_min:y_max, x_min:x_max]
            
            # --- g. 缩放：将裁剪出的ROI缩放到 512x512 ---
            final_image = cv2.resize(cropped_image, TARGET_SIZE, interpolation=cv2.INTER_LINEAR)
            final_mask = cv2.resize(cropped_mask, TARGET_SIZE, interpolation=cv2.INTER_NEAREST)
            
            # --- h. 保存到新目录 ---
            final_image_path = os.path.join(output_img_dir, f'{img_id}.png')
            final_mask_path = os.path.join(output_mask_dir, f'{img_id}.bmp')
            
            cv2.imwrite(final_image_path, final_image)
            cv2.imwrite(final_mask_path, final_mask)
            
            processed_count += 1
            
        except Exception as e:
            print(f"处理 {img_path} 时发生错误: {e}")
            
    return processed_count

# --- 3. 找到所有原始图像文件 ---
train_img_paths = glob.glob(os.path.join(DS_TRAIN_PATH, 'Images/GLAUCOMA/*.png')) + \
                  glob.glob(os.path.join(DS_TRAIN_PATH, 'Images/NORMAL/*.png'))
                  
test_img_paths = glob.glob(os.path.join(DS_TEST_PATH, 'Images/glaucoma/*.png')) + \
                 glob.glob(os.path.join(DS_TEST_PATH, 'Images/normal/*.png'))

# --- 4. 执行处理 (注意现在调用时传入了不同的输出路径) ---
print(f"开始处理 {len(train_img_paths)} 张 Drishti-GS 训练图像...")
train_gt_path = os.path.join(DS_TRAIN_PATH, 'GT')
# --- 调用训练集处理 ---
count_train = process_dataset(train_img_paths, train_gt_path, OUTPUT_IMG_DIR_TRAIN, OUTPUT_MASK_DIR_TRAIN)
print(f"成功处理 {count_train} 张训练图像。")
print(f"保存至: {OUTPUT_DIR_TRAIN}")


print(f"\n开始处理 {len(test_img_paths)} 张 Drishti-GS 测试图像...")
test_gt_path = os.path.join(DS_TEST_PATH, 'Test_GT')
# --- 调用测试集处理 ---
count_test = process_dataset(test_img_paths, test_gt_path, OUTPUT_IMG_DIR_TEST, OUTPUT_MASK_DIR_TEST)
print(f"成功处理 {count_test} 张测试图像。")
print(f"保存至: {OUTPUT_DIR_TEST}")

print(f"\n--- 预处理完成! ---")