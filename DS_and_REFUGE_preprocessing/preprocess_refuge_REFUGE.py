import cv2
import numpy as np
import os
import glob
from tqdm import tqdm

# --- 1. 定义常量 ---
PROJECT_ROOT = '.' 

# 原始 REFUGE 数据集路径 (根据你的 project_all_tree.txt)
REFUGE_TRAIN_IMAGES = [
    './data/Refuge/Training400/Glaucoma/',
    './data/Refuge/Training400/Non-Glaucoma/',
]
REFUGE_TRAIN_MASKS = [
    './data/Refuge/Annotation-Training400/Disc_Cup_Masks/Glaucoma/',
    './data/Refuge/Annotation-Training400/Disc_Cup_Masks/Non-Glaucoma/',
]

# 我们要创建的新的、干净的源域数据集目录
OUTPUT_DIR_TRAIN = os.path.join(PROJECT_ROOT, 'data/REFUGE_preprocessed_Train')
OUTPUT_IMG_DIR = os.path.join(OUTPUT_DIR_TRAIN, 'images')
OUTPUT_MASK_DIR = os.path.join(OUTPUT_DIR_TRAIN, 'masks')

# --- [關鍵修改] 添加缺失的常量 ---
# 从 Drishti/Val 脚本中借鉴来的统一配置
TARGET_SIZE = (512, 512)
PADDING = 30 
# ---------------------------------

# 我们的统一掩码值 (这个您已经有了)
MASK_VALS = {'cup': 255, 'disc': 128, 'bg': 0}

# --- 2. 创建输出目录 ---
os.makedirs(OUTPUT_IMG_DIR, exist_ok=True)
os.makedirs(OUTPUT_MASK_DIR, exist_ok=True)

def process_refuge_dataset(image_dirs, mask_dirs):
    """
    循环处理所有 REFUGE 训练图像：
    1. 将掩码转换为 [0, 128, 255] 格式
    2. 执行“先裁剪、后缩放” (与 Val 和 Drishti 脚本一致)
    """
    processed_count = 0
    
    # 查找所有图像
    image_paths = []
    for d in image_dirs:
        image_paths.extend(glob.glob(os.path.join(d, '*.jpg'))) # 原始图像是 .jpg
    
    print(f"找到了 {len(image_paths)} 张 REFUGE 训练图像。")

    for img_path in tqdm(image_paths):
        try:
            # --- a. 构建文件路径 ---
            img_name_with_ext = os.path.basename(img_path) # e.g., 'g0001.jpg'
            img_id = img_name_with_ext.split('.')[0] # e.g., 'g0001'
            
            mask_path_g = os.path.join(mask_dirs[0], f'{img_id}.bmp') # Glaucoma 掩码路径
            mask_path_n = os.path.join(mask_dirs[1], f'{img_id}.bmp') # Non-Glaucoma 掩码路径
            
            mask_path = None
            if os.path.exists(mask_path_g):
                mask_path = mask_path_g
            elif os.path.exists(mask_path_n):
                mask_path = mask_path_n
            else:
                print(f"警告：找不到 {img_id}.bmp 的掩码，跳过。")
                continue

            # --- b. 读取原始掩码 ---
            # 原始 REFUGE 格式为：背景=255, 视盘=128, 视杯=0
            original_mask = cv2.imread(mask_path, cv2.IMREAD_GRAYSCALE)
            
            if original_mask is None:
                print(f"警告：读取掩码失败，跳过: {mask_path}")
                continue
                
            h, w = original_mask.shape[:2]

            # --- c. 执行“相反”的映射，转换为我们的统一格式 ---
            new_mask = np.full((h, w), MASK_VALS['bg'], dtype=np.uint8)
            new_mask[original_mask == 128] = MASK_VALS['disc']
            new_mask[original_mask == 0] = MASK_VALS['cup']
            
            # --- [關鍵修改] 添加 Crop-then-Resize 邏輯 ---
            
            # --- d. 定位：从新掩码计算边界框 ---
            y_indices, x_indices = np.nonzero(new_mask > 0)
            
            if len(y_indices) == 0:
                print(f"警告：REFUGE 掩码 {img_id} 为空，跳过。")
                continue
            
            x_min = np.min(x_indices)
            x_max = np.max(x_indices)
            y_min = np.min(y_indices)
            y_max = np.max(y_indices)

            # --- e. 读取原始图像 (移到这里) ---
            original_image = cv2.imread(img_path)
            if original_image is None:
                print(f"警告：读取图像失败，跳过: {img_path}")
                continue
            
            # --- f. 应用安全边距 (Padding) ---
            x_min = max(0, x_min - PADDING)
            y_min = max(0, y_min - PADDING)
            x_max = min(w, x_max + PADDING)
            y_max = min(h, y_max + PADDING)
            
            # --- g. 裁剪：从原始图像和新掩码中裁剪出ROI ---
            cropped_image = original_image[y_min:y_max, x_min:x_max]
            cropped_mask = new_mask[y_min:y_max, x_min:x_max]
            
            if cropped_image.shape[0] == 0 or cropped_image.shape[1] == 0:
                print(f"警告：裁剪 {img_id} 后的图像为空，跳过。")
                continue

            # --- h. 缩放：将裁剪出的ROI缩放到 512x512 ---
            final_image = cv2.resize(cropped_image, TARGET_SIZE, interpolation=cv2.INTER_LINEAR)
            final_mask = cv2.resize(cropped_mask, TARGET_SIZE, interpolation=cv2.INTER_NEAREST)
            
            # --- [關鍵修改] i. 保存处理后的图像和掩码 ---
            final_image_path = os.path.join(OUTPUT_IMG_DIR, f'{img_id}.png')
            final_mask_path = os.path.join(OUTPUT_MASK_DIR, f'{img_id}.bmp') 
            
            cv2.imwrite(final_image_path, final_image)   # 保存裁剪和缩放后的图像
            cv2.imwrite(final_mask_path, final_mask)     # 保存裁剪和缩放后的掩码
            
            processed_count += 1
            
        except Exception as e:
            print(f"处理 {img_path} 时发生错误: {e}")
            
    return processed_count

# --- 3. 执行处理 ---
print(f"开始处理 REFUGE 训练数据集...")
count_train = process_refuge_dataset(REFUGE_TRAIN_IMAGES, REFUGE_TRAIN_MASKS)

print(f"\n--- REFUGE 预处理完成! ---")
print(f"成功处理 {count_train} 张图像和掩码并保存至:")
print(f"图像: {OUTPUT_IMG_DIR}")
print(f"掩码: {OUTPUT_MASK_DIR}")