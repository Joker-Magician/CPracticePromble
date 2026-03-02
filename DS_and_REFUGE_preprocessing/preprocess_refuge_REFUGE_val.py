import cv2
import numpy as np
import os
import glob
from tqdm import tqdm

# --- 1. 定义常量 ---
PROJECT_ROOT = '.' 

# --- 关键修改：定义 REFUGE 验证集 (Validation) 的原始路径 ---
# 这些路径来自你的 RefTtoRefVal.py 配置文件
REFUGE_VAL_IMAGES = [
    './data/Refuge/REFUGE-Validation400/',
]
REFUGE_VAL_MASKS = [
    './data/Refuge/REFUGE-Validation400-GT/Disc_Cup_Masks/',
]

# --- 关键修改：定义新的、预处理过的“验证集”输出目录 ---
OUTPUT_DIR_VAL = os.path.join(PROJECT_ROOT, 'data/REFUGE_preprocessed_Val')
OUTPUT_IMG_DIR = os.path.join(OUTPUT_DIR_VAL, 'images')
OUTPUT_MASK_DIR = os.path.join(OUTPUT_DIR_VAL, 'masks')

# --- 从 Drishti 脚本中借鉴来的统一配置 ---
TARGET_SIZE = (512, 512)
PADDING = 30 
# 我们的统一掩码值 (与 preprocess_refuge.py 一致)
MASK_VALS = {'cup': 255, 'disc': 128, 'bg': 0}

# --- 2. 创建所有输出目录 ---
os.makedirs(OUTPUT_IMG_DIR, exist_ok=True)
os.makedirs(OUTPUT_MASK_DIR, exist_ok=True)


def process_refuge_val_dataset(image_dirs, mask_dirs):
    """
    循环处理所有 REFUGE 验证集图像：
    1. 将掩码转换为我们的 [0, 128, 255] 格式
    2. 执行与 Drishti-GS 完全一致的“先裁剪、后缩放”
    """
    processed_count = 0
    
    # 查找所有图像
    image_paths = []
    for d in image_dirs:
        # 验证集图像可能是 .jpg, .png, .bmp, 我们用 * 来匹配所有
        image_paths.extend(glob.glob(os.path.join(d, '*.*'))) 
    
    print(f"找到了 {len(image_paths)} 张 REFUGE 验证集图像。")

    for img_path in tqdm(image_paths):
        try:
            # --- a. 构建文件路径 ---
            img_name_with_ext = os.path.basename(img_path) 
            img_id = img_name_with_ext.split('.')[0] # e.g., 'V0001'
            
            # 找到对应的掩码路径
            # 验证集的掩码和训练集在不同文件夹，所以我们只用一个 mask_dirs 列表
            mask_path = os.path.join(mask_dirs[0], f'{img_id}.bmp') 
            
            if not os.path.exists(mask_path):
                print(f"警告：找不到 {img_id}.bmp 的掩码，跳过。")
                continue

            # --- b. 读取原始掩码和图像 ---
            # 原始 REFUGE 格式：背景=255, 视盘=128, 视杯=0
            original_mask = cv2.imread(mask_path, cv2.IMREAD_GRAYSCALE)
            image = cv2.imread(img_path) 
            
            if original_mask is None:
                print(f"警告：读取掩码失败，跳过: {mask_path}")
                continue
            if image is None:
                print(f"警告：读取图像失败，跳过: {img_path}")
                continue
                
            h, w = original_mask.shape[:2]

            # --- c. 执行“相反”的映射，转换为我们的统一格式 ---
            new_mask = np.full((h, w), MASK_VALS['bg'], dtype=np.uint8)
            new_mask[original_mask == 128] = MASK_VALS['disc']
            new_mask[original_mask == 0] = MASK_VALS['cup']
            
            # --- d. 定位：从新掩码计算边界框 (从 Drishti 脚本复制的逻辑) ---
            # 我们从 new_mask (>0) 中寻找视盘和视杯
            y_indices, x_indices = np.nonzero(new_mask > 0)
            
            if len(y_indices) == 0:
                print(f"警告：REFUGE 掩码 {img_id} 为空，跳过。")
                continue
            
            x_min = np.min(x_indices)
            x_max = np.max(x_indices)
            y_min = np.min(y_indices)
            y_max = np.max(y_indices)
            
            # --- e. 应用安全边距 (Padding) ---
            x_min = max(0, x_min - PADDING)
            y_min = max(0, y_min - PADDING)
            x_max = min(w, x_max + PADDING)
            y_max = min(h, y_max + PADDING)
            
            # --- f. 裁剪：从原始图像和新掩码中裁剪出ROI ---
            cropped_image = image[y_min:y_max, x_min:x_max]
            cropped_mask = new_mask[y_min:y_max, x_min:x_max]
            
            if cropped_image.shape[0] == 0 or cropped_image.shape[1] == 0:
                print(f"警告：裁剪 {img_id} 后的图像为空，跳过。")
                continue

            # --- g. 缩放：将裁剪出的ROI缩放到 512x512 ---
            final_image = cv2.resize(cropped_image, TARGET_SIZE, interpolation=cv2.INTER_LINEAR)
            final_mask = cv2.resize(cropped_mask, TARGET_SIZE, interpolation=cv2.INTER_NEAREST)
            
            # --- h. 保存到新目录 ---
            final_image_path = os.path.join(OUTPUT_IMG_DIR, f'{img_id}.png') # 统一保存为 .png
            final_mask_path = os.path.join(OUTPUT_MASK_DIR, f'{img_id}.bmp') # 保持 .bmp 以匹配Drishti
            
            cv2.imwrite(final_image_path, final_image)
            cv2.imwrite(final_mask_path, final_mask)
            
            processed_count += 1
            
        except Exception as e:
            print(f"处理 {img_path} 时发生错误: {e}")
            
    return processed_count

# --- 3. 执行处理 ---
print(f"开始处理 REFUGE 验证集...")
count_val = process_refuge_val_dataset(REFUGE_VAL_IMAGES, REFUGE_VAL_MASKS)

print(f"\n--- REFUGE 验证集预处理完成! ---")
print(f"成功处理 {count_val} 张图像和掩码并保存至:")
print(f"图像: {OUTPUT_IMG_DIR}")
print(f"掩码: {OUTPUT_MASK_DIR}")