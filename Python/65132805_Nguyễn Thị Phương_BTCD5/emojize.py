import emoji


text = input("Input: ")

# Chuyển mã emoji sang biểu tượng cảm xúc thật
# use_aliases=True giúp nhận cả bí danh như :thumbsup:
output = emoji.emojize(text, language='alias')

print("Output:", output)
