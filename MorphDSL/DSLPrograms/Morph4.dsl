a = load(".\braintumor.bmp")
b = erode(BOX(1),a)
c = subtract(a,b)
