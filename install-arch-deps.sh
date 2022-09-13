#!/bin/bash

sudo pacman -S xclip maim xorg xorg-server picom feh dunst acpi pcmanfm firefox lxappearance neofetch xarchiver zsh zsh-autosuggestions zsh-syntax-highlighting --noconfirm --needed

git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ~/.p10k
