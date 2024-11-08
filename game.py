# Write a pygame game to show the user a random picture from the data set
# Give 4 buttons for the 4 categories
# Compare the user's answer to the models answer (use model_07.29.21.09.48_a916)

import pygame
import random
import torch
import torch.nn as nn
import torch.optim as optim
import model as model_script
from torchvision import transforms
from PIL import Image
import numpy as np

# Constants
WIDTH = 800
HEIGHT = 600
FPS = 6

# Initialize pygame
pygame.init()
pygame.mixer.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Guess the Category!")
clock = pygame.time.Clock()

# Load the model
model = model_script.Model()
model.load_state_dict(torch.load("./Models/model_07.30.15.34.28_a932_t14.pth", weights_only=True))
model.eval()

# Load the dataset
dataset = model_script.Dataset(data_dir="./datajpg/")

player_score = 0
model_score = 0
attempts = 0

image_tensor = None
image_label = None
image_file_dir = None

def get_new_image():
    global image_tensor, image_label, image_file_dir
    
    index = random.randint(0, 5631)
    image_tensor = dataset[index][0]
    image_label = dataset[index][1]
    image_file_dir = dataset.get_file_dir(index)

get_new_image()
    
run = True
while run:
    clock.tick(FPS)
    
    image = pygame.image.load(image_file_dir)
    image = pygame.transform.scale(image, (300, 300))
    screen.blit(image, (400, 100))
    
    # Create buttons for the 4 categories (cloudy, desert, forest, water)
    font = pygame.font.Font(None, 36)
    cloudy_button = pygame.Rect(50, 50, 200, 50)
    desert_button = pygame.Rect(50, 150, 200, 50)
    forest_button = pygame.Rect(50, 250, 200, 50)
    water_button = pygame.Rect(50, 350, 200, 50)
    
    pygame.draw.rect(screen, (255, 0, 0), cloudy_button)
    pygame.draw.rect(screen, (255, 0, 0), desert_button)
    pygame.draw.rect(screen, (255, 0, 0), forest_button)
    pygame.draw.rect(screen, (255, 0, 0), water_button)
    
    cloudy_text = font.render("Cloudy", True, (255, 255, 255))
    desert_text = font.render("Desert", True, (255, 255, 255))
    forest_text = font.render("Forest", True, (255, 255, 255))
    water_text = font.render("Water", True, (255, 255, 255))
    
    screen.blit(cloudy_text, (100, 60))
    screen.blit(desert_text, (100, 160))
    screen.blit(forest_text, (100, 260))
    screen.blit(water_text, (100, 360))
    
    user_guess = None
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
        # Check if the user clicked on a button
        elif event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos
            if cloudy_button.collidepoint(x, y):
                user_guess = "cloudy"
            elif desert_button.collidepoint(x, y):
                user_guess = "desert"
            elif forest_button.collidepoint(x, y):
                user_guess = "forest"
            elif water_button.collidepoint(x, y):
                user_guess = "water"
    
    if user_guess is not None:
        # Compare the user's guess to the model's guess
        with torch.no_grad():
            model_guess = model(image_tensor.unsqueeze(0))
            model_guess = torch.argmax(model_guess).item()
            
            if model_script.label_dict[model_guess] == model_script.label_dict[image_label]: model_score += 1
            if user_guess == model_script.label_dict[image_label]: player_score += 1
            attempts += 1
            
            print(f"Player: {player_score}, Model: {model_score}, Attempts: {attempts}")
        
        # Display Model guess & real value
        player_text_background = pygame.Rect(420, 450, 350, 100)
        pygame.draw.rect(screen, (0, 0, 0), player_text_background)
        
        label_text = font.render(f"It was {model_script.label_dict[image_label]}", True, (255, 255, 255))
        model_text = font.render(f"Model guessed {model_script.label_dict[model_guess]}", True, (255, 255, 255))
        screen.blit(label_text, (420, 450))
        screen.blit(model_text, (420, 500))
        
        get_new_image()
    
    if attempts == 0:
        pygame.display.flip()
        continue
    
    # Display Model accuracy & Player accuracy
    player_text_background = pygame.Rect(50, 450, 300, 100)
    pygame.draw.rect(screen, (0, 0, 0), player_text_background)
    
    player_text = font.render(f"Player Accuracy: {round(player_score/attempts*100, 2)}%", True, (255, 255, 255))
    model_text = font.render(f"Model Accuracy: {round(model_score/attempts*100, 2)}%", True, (255, 255, 255))
    screen.blit(player_text, (50, 450))
    screen.blit(model_text, (50, 500))
    
    pygame.display.flip()
