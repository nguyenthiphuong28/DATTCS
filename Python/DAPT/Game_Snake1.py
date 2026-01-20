
import pygame
import time
import random
import sys
import math
import json
import os

# Khởi tạo pygame
pygame.init()
pygame.mixer.init()

# Màu sắc
white = (255, 255, 255)
black = (40, 40, 40)
dark_green = (0, 100, 0)
light_green = (50, 205, 50)
red = (255, 0, 0)
gold = (255, 215, 0)
dark_red = (139, 0, 0)
background = (25, 25, 40)
snake_body = (34, 139, 34)
button_color = (70, 70, 90)
button_hover = (90, 90, 110)
leaderboard_color = (60, 60, 80)
highlight_color = (100, 180, 100)
highlight_border = (50, 150, 50)

# Thêm màu mới cho bánh quy và kẹo
cookie_color = (218, 165, 32)
cookie_hole = (139, 69, 19)
candy_color = (255, 105, 180)
candy_wrapper = (255, 20, 147)

# Kích thước màn hình
width, height = 800, 600
game_display = pygame.display.set_mode((width, height))
pygame.display.set_caption('Snake Game với Âm thanh - Đi Xuyên Tường')

# Đồng hồ
clock = pygame.time.Clock()

# Kích thước khối và tốc độ
block_size = 20
easy_speed = 7
medium_speed = 10
hard_speed = 13

# Kích thước nền menu (lớn hơn cho dễ đọc chữ)
menu_block_size = 40

# Thêm vùng chơi (không bao gồm thanh điểm)
game_area_y = 60  # Bắt đầu từ dưới thanh điểm
game_area_height = height - game_area_y

# Font chữ - thêm font nhỏ hơn cho leaderboard
try:
    font_style = pygame.font.SysFont("segoeui", 22)
    score_font = pygame.font.SysFont("segoeui", 30, bold=True)
    title_font = pygame.font.SysFont("segoeui", 45, bold=True)
    button_font = pygame.font.SysFont("segoeui", 26, bold=True)
    info_font = pygame.font.SysFont("segoeui", 18)
    leaderboard_font = pygame.font.SysFont("segoeui", 32, bold=True)  # Tăng từ 28 lên 32
    leaderboard_header_font = pygame.font.SysFont("segoeui", 24, bold=True)  # Tăng từ 20 lên 24
    leaderboard_entry_font = pygame.font.SysFont("segoeui", 22)  # Giữ nguyên
    input_font = pygame.font.SysFont("segoeui", 28)
except:
    font_style = pygame.font.SysFont("arial", 22)
    score_font = pygame.font.SysFont("arial", 30, bold=True)
    title_font = pygame.font.SysFont("arial", 45, bold=True)
    button_font = pygame.font.SysFont("arial", 26, bold=True)
    info_font = pygame.font.SysFont("arial", 18)
    leaderboard_font = pygame.font.SysFont("arial", 32, bold=True)
    leaderboard_header_font = pygame.font.SysFont("arial", 24, bold=True)
    leaderboard_entry_font = pygame.font.SysFont("arial", 22)
    input_font = pygame.font.SysFont("arial", 28)

# File lưu leaderboard
LEADERBOARD_FILE = "snake_leaderboard.json"

# Khởi tạo âm thanh
try:
    # Thử load file âm thanh
    eat_sound = pygame.mixer.Sound("thuong.mp3")
    special_eat_sound = pygame.mixer.Sound("dacbiet.mp3")
    crash_sound = pygame.mixer.Sound("game_over.mp3")
    sound_available = True
    print("Đã tải file âm thanh thành công!")
except:
    # Nếu không có file, tạo âm thanh
    eat_sound = None
    special_eat_sound = None
    crash_sound = None
    sound_available = eat_sound is not None
    if sound_available:
        print("Đã tạo âm thanh thành công!")
    else:
        print("Không thể tạo âm thanh. Game sẽ chạy không có âm thanh.")

# ============================================
# HÀM QUẢN LÝ LEADERBOARD
# ============================================

def load_leaderboard():
    """Tải leaderboard từ file JSON"""
    if os.path.exists(LEADERBOARD_FILE):
        try:
            with open(LEADERBOARD_FILE, 'r', encoding='utf-8') as file:
                return json.load(file)
        except:
            return []
    return []

def save_leaderboard(leaderboard):
    """Lưu leaderboard vào file JSON"""
    try:
        with open(LEADERBOARD_FILE, 'w', encoding='utf-8') as file:
            json.dump(leaderboard, file, ensure_ascii=False, indent=2)
        return True
    except:
        return False

def can_enter_leaderboard(score, difficulty):
    """Kiểm tra điểm có đủ cao để vào leaderboard không"""
    leaderboard = load_leaderboard()
    
    # Chỉ lấy top 5 cho độ khó hiện tại
    difficulty_leaderboard = [entry for entry in leaderboard if entry["difficulty"] == difficulty]
    
    # Nếu chưa đủ 5 người chơi
    if len(difficulty_leaderboard) < 5:
        return True
    
    # Sắp xếp theo điểm giảm dần
    difficulty_leaderboard.sort(key=lambda x: x["score"], reverse=True)
    
    # Kiểm tra nếu điểm cao hơn hoặc bằng điểm của người thứ 5
    if score >= difficulty_leaderboard[4]["score"]:
        return True
    
    return False

def add_to_leaderboard(name, score, difficulty):
    """Thêm người chơi vào leaderboard"""
    leaderboard = load_leaderboard()
    
    # Tạo entry mới
    new_entry = {
        "name": name,
        "score": score,
        "difficulty": difficulty,
        "date": time.strftime("%Y-%m-%d %H:%M:%S")
    }
    
    # Thêm vào leaderboard
    leaderboard.append(new_entry)
    
    # Lọc theo độ khó
    difficulty_leaderboard = [entry for entry in leaderboard if entry["difficulty"] == difficulty]
    
    # Sắp xếp theo điểm giảm dần
    difficulty_leaderboard.sort(key=lambda x: x["score"], reverse=True)
    
    # Giữ lại top 5
    difficulty_leaderboard = difficulty_leaderboard[:5]
    
    # Cập nhật lại leaderboard gốc
    leaderboard = [entry for entry in leaderboard if entry["difficulty"] != difficulty]
    # Thêm lại top 5
    leaderboard.extend(difficulty_leaderboard)
    
    # Lưu vào file
    save_leaderboard(leaderboard)
    
    return difficulty_leaderboard

def show_leaderboard(difficulty=None, highlight_index=-1):
    """Hiển thị leaderboard"""
    leaderboard = load_leaderboard()
    
    # Nếu có độ khó cụ thể, chỉ hiển thị leaderboard của độ khó đó
    if difficulty:
        leaderboard = [entry for entry in leaderboard if entry["difficulty"] == difficulty]
    
    # Sắp xếp theo điểm giảm dần
    leaderboard.sort(key=lambda x: x["score"], reverse=True)
    
    # Chỉ lấy top 5
    leaderboard = leaderboard[:5]
    
    return leaderboard, highlight_index


# HÀM VẼ
def draw_menu_background():
    """Vẽ nền menu với ô lớn hơn cho dễ đọc chữ"""
    for x in range(0, width, menu_block_size * 2):
        for y in range(0, height, menu_block_size * 2):
            pygame.draw.rect(game_display, (35,35,55), [x, y, menu_block_size, menu_block_size])
            pygame.draw.rect(game_display, (40,40,60), [x+menu_block_size, y+menu_block_size, menu_block_size, menu_block_size])

def draw_background():
    """Vẽ nền game trong vùng chơi"""
    for x in range(0, width, block_size * 2):
        for y in range(game_area_y, height, block_size * 2):
            pygame.draw.rect(game_display, (35,35,55), [x, y, block_size, block_size])
            pygame.draw.rect(game_display, (40,40,60), [x+block_size, y+block_size, block_size, block_size])

def draw_leaderboard(leaderboard, y_offset=0, highlight_index=-1, is_input_screen=False):
    """Vẽ bảng leaderboard với khung to hơn"""
    # Tính toán kích thước dựa trên loại màn hình
    if is_input_screen:
        # Màn hình nhập tên 
        leaderboard_width = 720 
        leaderboard_height = 400  
        leaderboard_x = (width - leaderboard_width) // 2
        leaderboard_y = 80 + y_offset  
        row_height = 60  
        # Tăng khoảng cách giữa các cột để chữ không bị dính
        column_spacing = {
            "rank": 60,      
            "name": 160,     
            "score": 340,     
            "difficulty": 460, 
            "date": 580      
        }
    else:
        # Màn hình bình thường cũng cần to hơn
        leaderboard_width = 720
        leaderboard_height = 380
        leaderboard_x = (width - leaderboard_width) // 2
        leaderboard_y = 120 + y_offset
        row_height = 55
        column_spacing = {
            "rank": 60,
            "name": 160,
            "score": 340,
            "difficulty": 460,
            "date": 580
        }
    
    # Vẽ nền leaderboard với hiệu ứng bóng
    pygame.draw.rect(game_display, (40, 40, 60), 
                    [leaderboard_x - 5, leaderboard_y - 5, leaderboard_width + 10, leaderboard_height + 10])
    pygame.draw.rect(game_display, leaderboard_color, 
                    [leaderboard_x, leaderboard_y, leaderboard_width, leaderboard_height])
    pygame.draw.rect(game_display, gold, 
                    [leaderboard_x, leaderboard_y, leaderboard_width, leaderboard_height], 4)
    
    # Vẽ tiêu đề - to hơn
    if is_input_screen:
        title = leaderboard_font.render("TOP 5 NGƯỜI CHƠI", True, gold)
        title_rect = title.get_rect(center=(width//2, leaderboard_y + 45))
    else:
        title = leaderboard_font.render("TOP 5 NGƯỜI CHƠI", True, gold)
        title_rect = title.get_rect(center=(width//2, leaderboard_y + 45))
    
    game_display.blit(title, title_rect)
    
    # Vẽ tiêu đề cột - với khoảng cách lớn hơn
    col_y = leaderboard_y + 100 if is_input_screen else leaderboard_y + 100
    pygame.draw.line(game_display, gold, (leaderboard_x + 20, col_y), 
                    (leaderboard_x + leaderboard_width - 20, col_y), 3)
    
    # Tạo tiêu đề cột với font to hơn
    rank_text = leaderboard_header_font.render("HẠNG", True, gold)
    name_text = leaderboard_header_font.render("TÊN", True, gold)
    score_text = leaderboard_header_font.render("ĐIỂM", True, gold)
    difficulty_text = leaderboard_header_font.render("CHẾ ĐỘ", True, gold)
    date_text = leaderboard_header_font.render("THỜI GIAN", True, gold)
    
    # Canh chỉnh vị trí tiêu đề
    game_display.blit(rank_text, [leaderboard_x + column_spacing["rank"] - rank_text.get_width()//2, col_y - 35])
    game_display.blit(name_text, [leaderboard_x + column_spacing["name"] - name_text.get_width()//2, col_y - 35])
    game_display.blit(score_text, [leaderboard_x + column_spacing["score"] - score_text.get_width()//2, col_y - 35])
    game_display.blit(difficulty_text, [leaderboard_x + column_spacing["difficulty"] - difficulty_text.get_width()//2, col_y - 35])
    game_display.blit(date_text, [leaderboard_x + column_spacing["date"] - date_text.get_width()//2, col_y - 35])
    
    # Vẽ từng entry
    for i, entry in enumerate(leaderboard):
        entry_y = col_y + 15 + i * row_height
        
        # Highlight entry nếu cần
        if i == highlight_index:
            pygame.draw.rect(game_display, highlight_color, 
                           [leaderboard_x + 15, entry_y - 10, 
                            leaderboard_width - 30, row_height - 10])
            pygame.draw.rect(game_display, highlight_border, 
                           [leaderboard_x + 15, entry_y - 10, 
                            leaderboard_width - 30, row_height - 10], 2)
        
        # Màu cho top 3
        if i == 0:  # Hạng 1
            rank_color = gold
            name_color = gold
        elif i == 1:  # Hạng 2
            rank_color = (192, 192, 192)  # Bạc
            name_color = (192, 192, 192)
        elif i == 2:  # Hạng 3
            rank_color = (205, 127, 50)  # Đồng
            name_color = (205, 127, 50)
        else:
            rank_color = white
            name_color = white
        
        # Vẽ thông tin - với khoảng cách lớn hơn giữa các dòng
        rank = leaderboard_entry_font.render(f"{i+1}.", True, rank_color)
        name = leaderboard_entry_font.render(entry["name"][:15], True, name_color)  # Tăng từ 12 lên 15 ký tự
        score = leaderboard_entry_font.render(str(entry["score"]), True, white)
        
        # Format difficulty để hiển thị ngắn gọn
        diff_text = entry["difficulty"]
        if diff_text == "Trung bình":
            diff_text = "Trung bình"
        elif len(diff_text) > 8:
            diff_text = diff_text[:8]
            
        difficulty = leaderboard_entry_font.render(diff_text, True, white)

        # Format date để hiển thị tốt hơn
        date_display = entry["date"][:16]  # Chỉ lấy ngày và giờ
        if len(date_display) > 10:
            # Nếu có thời gian, hiển thị dạng ngắn hơn
            date_display = entry["date"][5:16]  # Bỏ năm, chỉ lấy tháng-ngày giờ
            
        date = leaderboard_entry_font.render(date_display, True, white)
        
        # Canh giữa các cột
        game_display.blit(rank, [leaderboard_x + column_spacing["rank"] - rank.get_width()//2, entry_y])
        game_display.blit(name, [leaderboard_x + column_spacing["name"] - name.get_width()//2, entry_y])
        game_display.blit(score, [leaderboard_x + column_spacing["score"] - score.get_width()//2, entry_y])
        game_display.blit(difficulty, [leaderboard_x + column_spacing["difficulty"] - difficulty.get_width()//2, entry_y])
        game_display.blit(date, [leaderboard_x + column_spacing["date"] - date.get_width()//2, entry_y])
    
    # Nếu leaderboard rỗng
    if not leaderboard:
        empty_text = leaderboard_entry_font.render("Chưa có người chơi nào!", True, white)
        empty_rect = empty_text.get_rect(center=(width//2, col_y + 60))
        game_display.blit(empty_text, empty_rect)
    
    return leaderboard_height

def draw_apple(x, y):
    """Vẽ táo (thức ăn thường)"""
    pygame.draw.circle(game_display, red, (x + block_size//2, y + block_size//2), block_size//2)
    pygame.draw.rect(game_display, dark_green, [x + block_size//2 - 2, y - 3, 4, 6])
    leaf_points = [
        (x + block_size//2, y - 2),
        (x + block_size//2 + 5, y - 5),
        (x + block_size//2 + 3, y - 2)
    ]
    pygame.draw.polygon(game_display, light_green, leaf_points)

def draw_gold(x, y):
    """Vẽ vàng (thức ăn đặc biệt)"""
    # Hình thoi đơn giản
    points = [
        (x + block_size//2, y),
        (x + block_size, y + block_size//2),
        (x + block_size//2, y + block_size),
        (x, y + block_size//2)
    ]
    pygame.draw.polygon(game_display, gold, points)
    pygame.draw.polygon(game_display, (220, 185, 0), points, 2)

def draw_cookie(x, y):
    """Vẽ bánh quy"""
    # Vẽ bánh quy
    pygame.draw.circle(game_display, cookie_color, (x + block_size//2, y + block_size//2), block_size//2)
    
    # Vẽ 7 lỗ nhỏ trang trí
    holes = [
        (x + block_size//3, y + block_size//3),
        (x + 2*block_size//3, y + block_size//3),
        (x + block_size//3, y + 2*block_size//3),
        (x + 2*block_size//3, y + 2*block_size//3),
        (x + block_size//2, y + block_size//4),
        (x + block_size//4, y + block_size//2),
        (x + 3*block_size//4, y + block_size//2),
    ]
    
    for hole in holes:
        pygame.draw.circle(game_display, cookie_hole, hole, block_size//12)

def draw_candy(x, y):
    """Vẽ kẹo"""
    # Vẽ thân kẹo
    pygame.draw.ellipse(game_display, candy_color, [x, y + block_size//4, block_size, block_size//2])
    pygame.draw.ellipse(game_display, candy_wrapper, [x, y + block_size//4, block_size, block_size//2], 2)
    
    # Vẽ vỏ kẹo ở hai đầu
    pygame.draw.ellipse(game_display, candy_wrapper, [x - 2, y + block_size//4 - 2, 4, block_size//2 + 4])
    pygame.draw.ellipse(game_display, candy_wrapper, [x + block_size - 2, y + block_size//4 - 2, 4, block_size//2 + 4])
    
    # Vẽ sọc trang trí
    for i in range(3):
        start_x = x + 5 + i * 5
        end_x = x + 5 + i * 5
        pygame.draw.line(game_display, white, (start_x, y + block_size//4 + 2), (end_x, y + 3*block_size//4 - 2), 1)

def draw_snake_segment(x, y, is_head=False, direction=None):
    """Vẽ một đoạn rắn"""
    # Vẽ đầu rắn
    if is_head:
        pygame.draw.circle(game_display, light_green, (x + block_size//2, y + block_size//2), block_size//2)
        pygame.draw.circle(game_display, dark_green, (x + block_size//2, y + block_size//2), block_size//2, 2)
        
        # Vẽ mắt rắn
        eye_radius = 3
        if direction == "RIGHT":
            left_eye = (x + block_size//2 + 5, y + block_size//2 - 5)
            right_eye = (x + block_size//2 + 5, y + block_size//2 + 5)
        elif direction == "LEFT":
            left_eye = (x + block_size//2 - 5, y + block_size//2 - 5)
            right_eye = (x + block_size//2 - 5, y + block_size//2 + 5)
        elif direction == "UP":
            left_eye = (x + block_size//2 - 5, y + block_size//2 - 5)
            right_eye = (x + block_size//2 + 5, y + block_size//2 - 5)
        else:
            left_eye = (x + block_size//2 - 5, y + block_size//2 + 5)
            right_eye = (x + block_size//2 + 5, y + block_size//2 + 5)
        
        pygame.draw.circle(game_display, black, left_eye, eye_radius)
        pygame.draw.circle(game_display, black, right_eye, eye_radius)
        
        # Vẽ lưỡi rắn
        if direction in ["RIGHT", "LEFT"]:
            tongue_length = 6
            if direction == "RIGHT":
                tongue_start = (x + block_size, y + block_size//2)
                tongue_end = (x + block_size + tongue_length, y + block_size//2)
            else:
                tongue_start = (x, y + block_size//2)
                tongue_end = (x - tongue_length, y + block_size//2)
            pygame.draw.line(game_display, red, tongue_start, tongue_end, 2)
    
    # Vẽ thân rắn
    else:
        pygame.draw.circle(game_display, snake_body, (x + block_size//2, y + block_size//2), block_size//2 - 1)
        pygame.draw.circle(game_display, dark_green, (x + block_size//2, y + block_size//2), block_size//2 - 1, 1)

def our_snake(snake_list, direction):
    """Vẽ toàn bộ rắn"""
    for i, segment in enumerate(snake_list):
        is_head = (i == len(snake_list) - 1)
        draw_snake_segment(segment[0], segment[1], is_head, direction if is_head else None)

def message(msg, color, y_displace=0, size="medium", font=None, center_x=True):
    """Hiển thị thông báo"""
    if size == "large":
        font_obj = title_font
    elif size == "small":
        font_obj = info_font
    else:
        font_obj = font_style if font is None else font
        
    mesg = font_obj.render(msg, True, color)
    if center_x:
        text_rect = mesg.get_rect(center=(width/2, height/3 + y_displace))
    else:
        text_rect = mesg.get_rect(midleft=(width/3, height/3 + y_displace))
    game_display.blit(mesg, text_rect)

def draw_score(score, length, difficulty):
    """Vẽ điểm số"""
    # Vẽ thanh điểm ở trên cùng
    pygame.draw.rect(game_display, (50, 50, 70), [0, 0, width, game_area_y])
    pygame.draw.line(game_display, gold, (0, game_area_y), (width, game_area_y), 3)
    
    score_text = score_font.render(f"Điểm: {score}", True, white)
    length_text = font_style.render(f"Độ dài: {length}", True, white)
    diff_text = font_style.render(f"Chế độ: {difficulty}", True, white)
    
    # Canh chỉnh vị trí trong thanh điểm
    game_display.blit(score_text, [20, 15])
    game_display.blit(length_text, [200, 18])
    game_display.blit(diff_text, [550, 18])

def get_speed_level(length, base_speed):
    """Điều chỉnh tốc độ dựa trên độ dài rắn"""
    if length < 5:
        return base_speed
    elif length < 10:
        return base_speed + 2
    elif length < 15:
        return base_speed + 4
    else:
        return base_speed + 6

def draw_button(text, x, y, width, height, inactive_color, active_color, action=None, difficulty=None):
    """Vẽ nút bấm"""
    mouse = pygame.mouse.get_pos()
    click = pygame.mouse.get_pressed()
    
    if x + width > mouse[0] > x and y + height > mouse[1] > y:
        pygame.draw.rect(game_display, active_color, (x, y, width, height))
        if click[0] == 1 and action is not None:
            if difficulty is not None:
                action(difficulty)
            else:
                action()
    else:
        pygame.draw.rect(game_display, inactive_color, (x, y, width, height))
    
    pygame.draw.rect(game_display, gold, (x, y, width, height), 2)
        
    text_surf = button_font.render(text, True, white)
    text_rect = text_surf.get_rect(center=((x + (width/2)), (y + (height/2))))
    game_display.blit(text_surf, text_rect)

# HÀM TIỆN ÍCH
def generate_food_position(snake_list=None):
    """Tạo vị trí thức ăn không trùng với rắn"""
    if snake_list is None:
        snake_list = []
    
    while True:
        x = round(random.randrange(0, width - block_size) / block_size) * block_size
        y = round(random.randrange(game_area_y, game_area_y + game_area_height - block_size) / block_size) * block_size
        
        # Kiểm tra không trùng với thân rắn
        valid_position = True
        for segment in snake_list:
            if x == segment[0] and y == segment[1]:
                valid_position = False
                break
                
        if valid_position:
            return x, y

def pause_game(difficulty, score, length):
    """Tạm dừng game"""
    paused = True
    while paused:
        game_display.fill(background)
        draw_background()
        
        message("TẠM DỪNG", gold, -50, "large")
        message(f"Điểm: {score} - Độ dài: {length}", white, 0)
        message(f"Chế độ: {difficulty}", white, 30)
        message("Nhấn ESC để tiếp tục", white, 70)
        message("Nhấn Q để thoát", white, 100)
        
        pygame.display.update()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    paused = False
                if event.key == pygame.K_q:
                    pygame.quit()
                    sys.exit()

# HÀM NHẬP TÊN NGƯỜI CHƠI (VỚI LEADERBOARD LỚN)
def input_player_name(score, difficulty, current_leaderboard):
    """Nhập tên người chơi với leaderboard to hơn"""
    input_active = True
    player_name = ""
    cursor_visible = True
    cursor_timer = 0
    
    # Tìm vị trí của người chơi trong leaderboard
    leaderboard_sorted = sorted(current_leaderboard, key=lambda x: x["score"], reverse=True)
    player_rank = -1
    
    for i, entry in enumerate(leaderboard_sorted):
        if score >= entry["score"]:
            player_rank = i
            break
    
    if player_rank == -1 and len(leaderboard_sorted) < 5:
        player_rank = len(leaderboard_sorted)
    
    while input_active:
        cursor_timer += 1
        if cursor_timer >= 30: 
            cursor_visible = not cursor_visible
            cursor_timer = 0
        
        game_display.fill(background)
        
        # Vẽ nền menu với ô lớn hơn
        draw_menu_background()
        
        # Hiển thị thông báo
        message("XIN CHÚC MỪNG!", gold, -180, "large")
        message(f"Bạn đã đạt được {score} điểm trong chế độ {difficulty}", white, -130)
        message("Điểm của bạn đủ cao để vào TOP 5!", light_green, -90)
        
        # Hiển thị leaderboard hiện tại với highlight vị trí của người chơi
        draw_leaderboard(leaderboard_sorted, -10, player_rank, is_input_screen=True)
        instruction_y = 380  
        message("Nhập tên của bạn (tối đa 15 ký tự):", white, instruction_y)
        
        # Vẽ ô nhập tên lớn hơn
        input_box = pygame.Rect(width//2 - 200, height//2 + 100, 400, 50)
        pygame.draw.rect(game_display, (50, 50, 70), input_box)
        pygame.draw.rect(game_display, gold, input_box, 3)
        
        # Vẽ tên đã nhập
        name_surface = input_font.render(player_name, True, white)
        game_display.blit(name_surface, (input_box.x + 15, input_box.y + 10))
        
        # Vẽ con trỏ nhấp nháy
        if cursor_visible:
            cursor_x = input_box.x + 15 + name_surface.get_width()
            pygame.draw.line(game_display, white, 
                           (cursor_x, input_box.y + 10),
                           (cursor_x, input_box.y + input_box.height - 10), 3)
        
        message("Nhấn ENTER để lưu, ESC để bỏ qua", white, 280)
        
        pygame.display.update()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RETURN or event.key == pygame.K_KP_ENTER:
                    if player_name.strip():  # Kiểm tra tên không rỗng
                        # Thêm vào leaderboard
                        updated_leaderboard = add_to_leaderboard(player_name.strip(), score, difficulty)
                        input_active = False
                        return updated_leaderboard
                
                elif event.key == pygame.K_ESCAPE:
                    input_active = False
                    return current_leaderboard
                
                elif event.key == pygame.K_BACKSPACE:
                    player_name = player_name[:-1]
                
                else:
                    # Kiểm tra nếu ký tự hợp lệ và tên chưa quá dài
                    if len(player_name) < 15 and event.unicode.isprintable():
                        player_name += event.unicode
        
        clock.tick(30)
    
    return current_leaderboard

# HÀM CHÍNH CỦA GAME
def game_loop(difficulty):
    """Vòng lặp chính của game"""
    # Đặt tốc độ cơ bản dựa trên độ khó
    if difficulty == "Dễ":
        base_speed = easy_speed
    elif difficulty == "Trung bình":
        base_speed = medium_speed
    else:
        base_speed = hard_speed
    
    game_over = False
    game_close = False

    # Khởi tạo vị trí rắn
    x1 = width / 2
    y1 = height / 2
    x1_change = 0
    y1_change = 0
    direction = "RIGHT"

    snake_list = []
    length_of_snake = 1

    # Tạo thức ăn thường
    food_type = random.choice(["apple", "cookie", "candy"])
    foodx, foody = generate_food_position(snake_list)

    # Tạo thức ăn đặc biệt
    special_food_active = False
    special_foodx = 0
    special_foody = 0
    special_food_timer = 0
    special_food_duration = 5

    score = 0
    speed = base_speed

    # Biến để kiểm soát thời gian tạo thức ăn đặc biệt
    last_special_food_time = time.time()
    special_food_cooldown = 8
    
    while not game_over:
        while game_close:
            game_display.fill(background)
            draw_background()
            message("GAME OVER!", red, -50, "large")
            message(f"Điểm cuối: {score} - Độ dài: {length_of_snake}", white, 0)
            message(f"Chế độ: {difficulty}", white, 30)
            
            # Kiểm tra xem điểm có đủ cao để vào leaderboard không
            if can_enter_leaderboard(score, difficulty):
                message("Điểm của bạn đủ cao để vào TOP 5!", gold, 60)
                message("Nhấn N để nhập tên, C để bỏ qua", white, 90)
            else:
                message("Nhấn C-Chọn chế độ | SPACE-Chơi lại | Q-Thoát", white, 60)
            
            pygame.display.update()
            
            # Xử lý sự kiện
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game_over = True
                    game_close = False
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_q:
                        game_over = True
                        game_close = False
                    if event.key == pygame.K_c:
                        # Quay lại màn hình chọn chế độ
                        game_close = False
                        show_difficulty_screen()
                        return
                    if event.key == pygame.K_SPACE:
                        # Chơi lại với cùng chế độ
                        game_loop(difficulty)
                        return
                    if event.key == pygame.K_n and can_enter_leaderboard(score, difficulty):
                        # Nhập tên để vào leaderboard
                        current_leaderboard = load_leaderboard()
                        difficulty_leaderboard = [entry for entry in current_leaderboard if entry["difficulty"] == difficulty]
                        input_player_name(score, difficulty, difficulty_leaderboard)
                        # Sau khi nhập tên, quay lại màn hình chọn chế độ
                        game_close = False
                        show_difficulty_screen()
                        return
        
        # Xử lý điều khiển rắn
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT and x1_change == 0:
                    x1_change = -block_size
                    y1_change = 0
                    direction = "LEFT"
                elif event.key == pygame.K_RIGHT and x1_change == 0:
                    x1_change = block_size
                    y1_change = 0
                    direction = "RIGHT"
                elif event.key == pygame.K_UP and y1_change == 0:
                    y1_change = -block_size
                    x1_change = 0
                    direction = "UP"
                elif event.key == pygame.K_DOWN and y1_change == 0:
                    y1_change = block_size
                    x1_change = 0
                    direction = "DOWN"
                elif event.key == pygame.K_ESCAPE:
                    pause_game(difficulty, score, length_of_snake)
                elif event.key == pygame.K_p:
                    # Phím P cũng để tạm dừng
                    pause_game(difficulty, score, length_of_snake)

        # ĐI XUYÊN TƯỜNG - Thay vì kiểm tra va chạm tường
        x1 += x1_change
        y1 += y1_change
        
        # Xử lý đi xuyên tường
        if x1 >= width:  # Ra khỏi bên phải
            x1 = 0  # Xuất hiện bên trái
        elif x1 < 0:  # Ra khỏi bên trái
            x1 = width - block_size  # Xuất hiện bên phải
        
        if y1 >= height:  # Ra khỏi đáy
            y1 = game_area_y  # Xuất hiện trên cùng của vùng chơi
        elif y1 < game_area_y:  # Ra khỏi đỉnh vùng chơi
            y1 = height - block_size  # Xuất hiện đáy màn hình
        
        game_display.fill(background)
        draw_background()
        
        # Vẽ thức ăn thường
        if food_type == "apple":
            draw_apple(foodx, foody)
        elif food_type == "cookie":
            draw_cookie(foodx, foody)
        else:  # candy
            draw_candy(foodx, foody)
        
        # Vẽ thức ăn đặc biệt nếu có
        if special_food_active:
            time_left = special_food_duration - (time.time() - special_food_timer)
            if time_left > 0:
                # Nhấp nháy khi sắp hết thời gian
                if time_left > 1 or int(time.time() * 5) % 2 == 0:
                    draw_gold(special_foodx, special_foody)
            else:
                special_food_active = False
        
        # Tạo thức ăn đặc biệt
        current_time = time.time()
        if (not special_food_active and 
            current_time - last_special_food_time > special_food_cooldown and 
            random.random() < 0.02):
            
            # Đảm bảo thức ăn đặc biệt không trùng với thức ăn thường và thân rắn
            special_foodx, special_foody = generate_food_position(snake_list + [[foodx, foody]])
            special_food_active = True
            special_food_timer = current_time
            last_special_food_time = current_time
        
        # Cập nhật rắn
        snake_head = [x1, y1]
        snake_list.append(snake_head)
        
        if len(snake_list) > length_of_snake:
            del snake_list[0]

        # Kiểm tra va chạm với chính mình
        for x in snake_list[:-1]:
            if x[0] == snake_head[0] and x[1] == snake_head[1]:
                if sound_available:
                    crash_sound.play()
                game_close = True

        our_snake(snake_list, direction)
        draw_score(score, length_of_snake, difficulty)
        pygame.display.update()

        # Kiểm tra ăn thức ăn thường
        if x1 == foodx and y1 == foody:
            food_type = random.choice(["apple", "cookie", "candy"])
            foodx, foody = generate_food_position(snake_list)
            length_of_snake += 1
            
            # Tạo điểm ngẫu nhiên 1 hoặc 2
            points = random.choice([1, 2])
            score += points
            
            speed = get_speed_level(length_of_snake, base_speed)
            if sound_available:
                eat_sound.play()
                
        # Kiểm tra ăn thức ăn đặc biệt
        if special_food_active and x1 == special_foodx and y1 == special_foody:
            special_food_active = False
            score += 4
            length_of_snake += 1
            speed = get_speed_level(length_of_snake, base_speed)
            if sound_available:
                special_eat_sound.play()

        clock.tick(speed)

    pygame.quit()
    sys.exit()

# HÀM HIỂN THỊ MÀN HÌNH
def show_start_screen():
    """Hiển thị màn hình bắt đầu"""
    start = False
    while not start:
        game_display.fill(background)
        
        # Vẽ nền menu với ô lớn hơn
        draw_menu_background()
        
        message("SNAKE GAME", light_green, -120, "large")
        message("Sử dụng các phím mũi tên để di chuyển", white, -30, "small")
        message("Ăn táo/bánh quy/kẹo: điểm ngẫu nhiên 1 or 2", red, 0, "small")
        message("Ăn vàng: 4 điểm", gold, 25, "small")
        message("ESC hoặc P: Tạm dừng", white, 50, "small")
        message("Tránh va vào chính mình!", white, 75, "small")
        message("Nhấn SPACE để chọn chế độ chơi", light_green, 130)
        # Vẽ minh họa các loại thức ăn
        draw_apple(width//2 - 60, height//2 + 200)
        draw_cookie(width//2 - 20, height//2 + 200)
        draw_candy(width//2 + 20, height//2 + 200)
        draw_gold(width//2 + 60, height//2 + 200)
        
        pygame.display.update()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    start = True
                if event.key == pygame.K_l:
                    # Hiển thị màn hình leaderboard trước
                    show_full_leaderboard_screen()

def show_difficulty_screen():
    """Hiển thị màn hình chọn độ khó"""
    difficulty_selected = False
    show_leaderboard_flag = False
    
    while not difficulty_selected:
        game_display.fill(background)
        
        # Vẽ nền menu với ô lớn hơn
        draw_menu_background()
        
        if not show_leaderboard_flag:
            message("CHỌN CHẾ ĐỘ CHƠI", light_green, -180, "large")
            
            draw_button("DỄ", width//2 - 150, height//2 - 100, 300, 60, button_color, button_hover, game_loop, "Dễ")
            draw_button("TRUNG BÌNH", width//2 - 150, height//2 - 20, 300, 60, button_color, button_hover, game_loop, "Trung bình")
            draw_button("KHÓ", width//2 - 150, height//2 + 60, 300, 60, button_color, button_hover, game_loop, "Khó")
            draw_button("XEM TOP 5", width//2 - 150, height//2 + 140, 300, 50, button_color, button_hover, None)
        else:
            # Hiển thị leaderboard tổng hợp
            message("TOP 5 NGƯỜI CHƠI TẤT CẢ CHẾ ĐỘ", light_green, -180, "large")
            
            # Load và hiển thị leaderboard
            leaderboard, _ = show_leaderboard()
            draw_leaderboard(leaderboard, -100)
            
            draw_button("QUAY LẠI", width//2 - 150, height - 80, 300, 50, button_color, button_hover, None)
        
        pygame.display.update()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse = pygame.mouse.get_pos()
                
                # Kiểm tra nút "XEM TOP 5"
                if not show_leaderboard_flag:
                    if width//2 - 150 < mouse[0] < width//2 + 150 and height//2 + 140 < mouse[1] < height//2 + 190:
                        show_leaderboard_flag = True
                else:
                    # Kiểm tra nút "QUAY LẠI"
                    if width//2 - 150 < mouse[0] < width//2 + 150 and height - 80 < mouse[1] < height - 30:
                        show_leaderboard_flag = False

def show_full_leaderboard_screen():
    """Hiển thị màn hình leaderboard đầy đủ"""
    viewing = True
    while viewing:
        game_display.fill(background)
        
        # Vẽ nền menu với ô lớn hơn
        draw_menu_background()
        
        message("TOP 5 NGƯỜI CHƠI TẤT CẢ CHẾ ĐỘ", light_green, -180, "large")
        
        # Load và hiển thị leaderboard
        leaderboard, _ = show_leaderboard()
        draw_leaderboard(leaderboard, -100)
        
        message("Nhấn ESC để quay lại", white, 200)
        
        pygame.display.update()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    viewing = False
# Chạy game
show_start_screen()
show_difficulty_screen()