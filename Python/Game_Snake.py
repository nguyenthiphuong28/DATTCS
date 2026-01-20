import pygame
import time
import random
import sys
import math

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

# Thêm màu mới cho bánh quy và kẹo
cookie_color = (218, 165, 32)
cookie_hole = (139, 69, 19)
candy_color = (255, 105, 180)
candy_wrapper = (255, 20, 147)

# Kích thước màn hình
width, height = 800, 600
game_display = pygame.display.set_mode((width, height))
pygame.display.set_caption('Snake Game với Âm thanh')

# Đồng hồ
clock = pygame.time.Clock()

# Kích thước khối và tốc độ
block_size = 20
easy_speed = 7
medium_speed = 10
hard_speed = 13

# Thêm vùng chơi (không bao gồm thanh điểm)
game_area_y = 60  # Bắt đầu từ dưới thanh điểm
game_area_height = height - game_area_y

# Font chữ
try:
    font_style = pygame.font.SysFont("segoeui", 22)
    score_font = pygame.font.SysFont("segoeui", 30, bold=True)
    title_font = pygame.font.SysFont("segoeui", 45, bold=True)
    button_font = pygame.font.SysFont("segoeui", 26, bold=True)
    info_font = pygame.font.SysFont("segoeui", 18)
except:
    font_style = pygame.font.SysFont("arial", 22)
    score_font = pygame.font.SysFont("arial", 30, bold=True)
    title_font = pygame.font.SysFont("arial", 45, bold=True)
    button_font = pygame.font.SysFont("arial", 26, bold=True)
    info_font = pygame.font.SysFont("arial", 18)

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


# Hàm vẽ táo (thức ăn thường)
def draw_apple(x, y):
    pygame.draw.circle(game_display, red, (x + block_size//2, y + block_size//2), block_size//2)
    pygame.draw.rect(game_display, dark_green, [x + block_size//2 - 2, y - 3, 4, 6])
    leaf_points = [
        (x + block_size//2, y - 2),
        (x + block_size//2 + 5, y - 5),
        (x + block_size//2 + 3, y - 2)
    ]
    pygame.draw.polygon(game_display, light_green, leaf_points)

# Hàm vẽ bánh quy
def draw_cookie(x, y):
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

# Hàm vẽ kẹo
def draw_candy(x, y):
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

# Hàm vẽ vàng (Thức ăn đặc biệt)
def draw_gold(x, y):
    # Hình thoi đơn giản
    points = [
        (x + block_size//2, y),
        (x + block_size, y + block_size//2),
        (x + block_size//2, y + block_size),
        (x, y + block_size//2)
    ]
    pygame.draw.polygon(game_display, gold, points)
    pygame.draw.polygon(game_display, (220, 185, 0), points, 2)

# Hàm vẽ rắn
def draw_snake_segment(x, y, is_head=False, direction=None):
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

# Hàm vẽ toàn bộ rắn
def our_snake(snake_list, direction):
    for i, segment in enumerate(snake_list):
        is_head = (i == len(snake_list) - 1)
        draw_snake_segment(segment[0], segment[1], is_head, direction if is_head else None)

# Hàm vẽ nền game - CHỈ VẼ TRONG VÙNG CHƠI
def draw_background():
    for x in range(0, width, block_size * 2):
        for y in range(game_area_y, height, block_size * 2):
            pygame.draw.rect(game_display, (35,35,55), [x, y, block_size, block_size])
            pygame.draw.rect(game_display, (40,40,60), [x+block_size, y+block_size, block_size, block_size])

# Hàm hiển thị văn bản
def message(msg, color, y_displace=0, size="medium", font=None):
    if size == "large":
        font_obj = title_font
    elif size == "small":
        font_obj = info_font
    else:
        font_obj = font_style if font is None else font
        
    mesg = font_obj.render(msg, True, color)
    text_rect = mesg.get_rect(center=(width/2, height/3 + y_displace))
    game_display.blit(mesg, text_rect)

# Hàm vẽ điểm
def draw_score(score, length, difficulty):
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

# Hàm điều chỉnh tốc độ
def get_speed_level(length, base_speed):
    if length < 5:
        return base_speed
    elif length < 10:
        return base_speed + 2
    elif length < 15:
        return base_speed + 4
    else:
        return base_speed + 6

# Hàm tạo nút bấm
def draw_button(text, x, y, width, height, inactive_color, active_color, action=None, difficulty=None):
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

# Hàm tạo vị trí thức ăn - CHỈ TRONG VÙNG CHƠI
def generate_food_position(snake_list=None):
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

# Hàm tạm dừng game
def pause_game(difficulty, score, length):
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

# Hàm chính của game
def game_loop(difficulty):
    # Đặt tốc độ cơ bản dựa trên độ khó
    if difficulty == "Dễ":
        base_speed = easy_speed
    elif difficulty == "Trung bình":
        base_speed = medium_speed
    else:
        base_speed = hard_speed
    
    game_over = False
    game_close = False

    # Khởi tạo vị trí rắn - TRONG VÙNG CHƠI
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
    # màn hình game over
    while not game_over:
        while game_close:
            game_display.fill(background)
            draw_background()
            message("GAME OVER!", red, -50, "large")
            message(f"Điểm cuối: {score} - Độ dài: {length_of_snake}", white, 0)
            message(f"Chế độ: {difficulty}", white, 30)
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
    # xử lý điều khiển rắn
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

        # Kiểm tra va chạm với tường - CHỈ TRONG VÙNG CHƠI
        if x1 >= width or x1 < 0 or y1 >= height or y1 < game_area_y:
            if sound_available:
                crash_sound.play()
            game_close = True

        x1 += x1_change
        y1 += y1_change
        
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
            
            # Lưu thông tin để hiển thị điểm tạm thời
            show_points = True
            points_text = f"+{points}"
            points_timer = 30  # Số frame hiển thị
            
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

# Hàm hiển thị màn hình chọn độ khó
def show_difficulty_screen():
    difficulty_selected = False
    while not difficulty_selected:
        game_display.fill(background)
        
        # Vẽ nền trong màn hình chọn chế độ
        for x in range(0, width, block_size * 2):
            for y in range(0, height, block_size * 2):
                pygame.draw.rect(game_display, (35,35,55), [x, y, block_size, block_size])
                pygame.draw.rect(game_display, (40,40,60), [x+block_size, y+block_size, block_size, block_size])
        
        message("CHỌN CHẾ ĐỘ CHƠI", light_green, -180, "large")
        
        draw_button("DỄ", width//2 - 150, height//2 - 100, 300, 60, button_color, button_hover, game_loop, "Dễ")
        draw_button("TRUNG BÌNH", width//2 - 150, height//2 - 20, 300, 60, button_color, button_hover, game_loop, "Trung bình")
        draw_button("KHÓ", width//2 - 150, height//2 + 60, 300, 60, button_color, button_hover, game_loop, "Khó")
        
        pygame.display.update()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

# Hàm hiển thị màn hình bắt đầu
def show_start_screen():
    start = False
    while not start:
        game_display.fill(background)
        
        # Vẽ nền trong màn hình bắt đầu
        for x in range(0, width, block_size * 2):
            for y in range(0, height, block_size * 2):
                pygame.draw.rect(game_display, (35,35,55), [x, y, block_size, block_size])
                pygame.draw.rect(game_display, (40,40,60), [x+block_size, y+block_size, block_size, block_size])
        
        message("SNAKE GAME", light_green, -120, "large")
        message("Sử dụng các phím mũi tên để di chuyển", white, -50, "small")
        message("Ăn táo/bánh quy/kẹo: điểm ngẫu nhiên 1 or 2", red, -20, "small")
        message("Ăn vàng: 4 điểm", gold, 5, "small")
        message("ESC hoặc P: Tạm dừng", white, 30, "small")
        message("Tránh va vào tường và chính mình!", white, 55, "small")
        message("Nhấn SPACE để chọn chế độ chơi", light_green, 90)
        
        # Vẽ minh họa các loại thức ăn
        draw_apple(width//2 - 60, height//2 + 150)
        draw_cookie(width//2 - 20, height//2 + 150)
        draw_candy(width//2 + 20, height//2 + 150)
        draw_gold(width//2 + 60, height//2 + 150)
        
        pygame.display.update()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    start = True

# Chạy game
show_start_screen()
show_difficulty_screen()