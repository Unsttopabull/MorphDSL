a = load(".\maribor.bmp")
b = SELECT normalize(mask) FROM a 
    WHERE 100 < area AND area < 1000 AND response > 5