echo off
clear

PATH=$PATH:../ogre_src_v1-8-1/build/bin:../boost-lib/lib:../zlib-1.2.11/lib:../FreeImage/:../ogre_src_v1-8-1/lib

make OGRE_PATH=../ogre_src_v1-8-1 BOOST_PATH=../boost-lib GAME_PATH=./Game_1_27_2017 FREEIMAGE_PATH=../FreeImage