from PIL import Image
import os
import string

#const uint8_t const name[] = {1, 1, 0,};

map = [(0, 0, 0, 0), (0, 0, 0, 255), (255, 255, 255, 255)]

f = open("sprites.h","w")

files = os.listdir()
files.remove("converter.py")
for fi in files:
    if (fi[-4:] == ".png"):
        has_alpha = "0"
        img = Image.open(fi, 'r')
        img_w, img_h = img.size
        pixels = list(img.getdata())

        color = ""
        alpha = ""

        for x in range(img_w):
            cstr = ""
            astr = ""
            for y in range(img_h):
                rgb = pixels[x+img_w*y]
                if (rgb == (0, 0, 0, 255)):
                    cstr = "0" + cstr
                    astr = "1" + astr
                elif (rgb == (255, 255, 255, 255)):
                    cstr = "1" + cstr
                    astr = "1" + astr
                else:
                    cstr = "0" + cstr
                    astr = "0" + astr
                    has_alpha = "1"
            if (img_h<32):
                padding = "0"*(32-img_h)
                cstr = padding + cstr
                astr = padding + astr
            color += "0b" + cstr + ", "
            alpha += "0b" + astr + ", "
            
        f.write("const int const "+fi[:-4]+"[] = {0b"+has_alpha+"000000000000000"+format(img_w, '08b')+format(img_h, '08b') +", \n"+color)
        if (has_alpha == "1"): f.write(alpha)
        f.write("};\n\n")


f.close()

