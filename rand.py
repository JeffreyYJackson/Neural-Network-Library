import os
import shutil
import random

paths = os.walk("./datajpg")
# pick 50 random images in the data set and copy them into ./test folder and print the names while reseting the previous names, should be "test1.jpg", "test2.jpg", etc.


zerotofiftytwo = list(range(0, 52))
print(zerotofiftytwo)
labels = {}

paths = os.walk("./datajpg/")
iters = 0
for path in paths:
    iters += 1
    for i in range(13):
        if iters == 1: continue
        
        # Pick random element in list of numbers and remove it
        index = zerotofiftytwo.pop(zerotofiftytwo.index(random.choice(zerotofiftytwo)))
        
        # Add (index, str.split(path[0], "/")[2]) to dictionary
        labels[index] = str.split(path[0], "/")[2]
        
        file_dir = f"{path[0]}/{str.split(path[0], "/")[2]}_{i}.jpg"
        print(f"test{index}.jpg")
        # copy the file:
        shutil.copy(file_dir, f"./test/test{index}.jpg")
        
# sort dict
labels = dict(sorted(labels.items()))
print(labels)