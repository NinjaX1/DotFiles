#!/bin/bash

sudo pacman -S xorg xorg-server xorg-xinit libx11 libxinerama libx11 webkit2gtk xclip maim picom feh dunst acpi pcmanfm lxappearance neofetch xarchiver zsh zsh-autosuggestions zsh-syntax-highlighting --noconfirm --needed

git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ~/.p10k