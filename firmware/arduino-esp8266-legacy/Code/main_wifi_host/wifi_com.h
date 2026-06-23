// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#ifndef WIFI_COM_H
#define WIFI_COM_H

#include <Arduino.h>

void wifi_init();
void get_cmd(int *cmd_angle, int *cmd_speed);

const char PROGMEM webpage[] = "<!DOCTYPE html> \n <html> \n <head> \n <title>R6 Drone Control</title> \n <script type=\"text/javascript\" src=\"http://code.jquery.com/jquery-1.10.2.min.js\">"
                               "</script> \n <meta name=\"viewport\" content=\"user-scalable=no\"> \n </head> \n <body  style=\"position: fixed; font-family: 'Gill Sans', 'Gill Sans MT', Calibri,"
                               " 'Trebuchet MS', sans-serif ; \n color:rgb(128, 128, 128); \n font-size: xx-large;\"> <style> body{overscroll-behavior-y: contain;}</style>"
                               "\n <p style=\"text-align: center;\"> \n X: <span id=\"x_coordinate\"> </span> \n Y:"
                               " <span id=\"y_coordinate\"> </span> \n Speed: <span id=\"speed\"> </span> % \n Angle: <span id=\"angle\"> </span> rad \n </p> \n <canvas id=\"canvas\" name=\"game\"></canvas>"
                               "  \n  \n  \n <script> \n var canvas, ctx; \n window.addEventListener('load', () => { \n canvas = document.getElementById('canvas'); \n ctx = canvas.getContext('2d'); \n resize();"
                               "  \n document.addEventListener('mousedown', startDrawing); \n document.addEventListener('mouseup', stopDrawing); \n document.addEventListener('mousemove', Draw);"
                               "  \n document.addEventListener('touchstart', startDrawing); \n document.addEventListener('touchend', stopDrawing); \n document.addEventListener('touchcancel', stopDrawing);"
                               "  \n document.addEventListener('touchmove', Draw); \n window.addEventListener('resize', resize); \n document.getElementById(\"x_coordinate\").innerText = 0;"
                               "  \n document.getElementById(\"y_coordinate\").innerText = 0; \n document.getElementById(\"speed\").innerText = 0; \n document.getElementById(\"angle\").innerText = 0;"
                               "  \n }); \n  \n var width, height, radius, x_orig, y_orig, delta_x, delta_y; \n function resize() { \n width = window.innerWidth; \n radius = 200; \n height = radius * 5;"
                               "  \n ctx.canvas.width = width; \n ctx.canvas.height = height; \n background(); \n joystick(width / 2, height / 2); \n } \n function background() { \n x_orig = width / 2;"
                               "  \n y_orig = height / 2; \n ctx.beginPath(); \n ctx.arc(x_orig, y_orig, radius + 20, 0, Math.PI * 2, true); \n ctx.fillStyle = '#ECE5E5'; \n ctx.fill(); \n } \n function"
                               " joystick(width, height) { \n ctx.beginPath(); \n ctx.arc(width, height, radius, 0, Math.PI * 2, true); \n ctx.fillStyle = '#F08080'; \n ctx.fill(); \n } \n let coord ="
                               " { x: 0, y: 0 }; \n let paint = false; \n function getPosition(event) { \n e = window.event || e; \n var mouse_x = e.clientX || e.touches[0].clientX; \n var mouse_y ="
                               " e.clientY || e.touches[0].clientY; \n coord.x = mouse_x - canvas.offsetLeft; \n coord.y = mouse_y - canvas.offsetTop; \n delta_x = coord.x - x_orig; \n delta_y = "
                               " -(coord.y - y_orig); \n } \n function is_it_in_the_circle() { \n var current_radius = Math.sqrt(Math.pow(delta_x, 2) + Math.pow(delta_y, 2)); \n if (radius >= current_radius)"
                               " return true; \n else return false; \n } \n var intervalId; \n var cmd_speed, cmd_angle; \n function startDrawing(event) { \n paint = true; \n getPosition(event); \n if (is_it_in_the_circle())"
                               " { \n ctx.clearRect(0, 0, canvas.width, canvas.height); \n background(); \n joystick(coord.x, coord.y); \n Draw(); \n } \n cmd_speed = 0; \n cmd_angle = 0;"
                               "  \n  \n intervalId = setInterval(Send, 500); \n  \n } \n function stopDrawing() { \n cmd_speed = 0; \n cmd_angle = 0; \n $.get(\"http://000.000.000.000:80/\", {an:cmd_angle , sp:cmd_speed});"
                               "  \n  \n paint = false; \n ctx.clearRect(0, 0, canvas.width, canvas.height); \n background(); \n joystick(width / 2, height / 2); \n document.getElementById(\"x_coordinate\").innerText ="
                               " 0; \n document.getElementById(\"y_coordinate\").innerText = 0; \n document.getElementById(\"speed\").innerText = 0; \n document.getElementById(\"angle\").innerText = "
                               " 0; \n  \n clearTimeout(intervalId); \n } \n  \n function Draw(event) { \n if (paint) { \n ctx.clearRect(0, 0, canvas.width, canvas.height); \n background(); \n var x, y, speed;"
                               "  \n var angle = Math.atan2(  (delta_y), (delta_x)  )  ; \n angle = angle.toFixed(1); \n if (is_it_in_the_circle()) { \n joystick(coord.x, coord.y); \n x = coord.x; \n y ="
                               " coord.y; \n } \n else { \n x = radius * Math.cos(angle) + x_orig; \n y = radius * (-Math.sin(angle)) + y_orig; \n joystick(x, y); \n } \n  \n getPosition(event); \n var speed ="
                               " Math.round(100 * Math.sqrt(Math.pow(x - x_orig, 2) + Math.pow(y - y_orig, 2)) / radius); \n var x_relative = Math.round(x - x_orig); \n var y_relative = "
                               " Math.round(-y + y_orig); \n  \n  \n  \n  \n document.getElementById(\"x_coordinate\").innerText =  x_relative; \n document.getElementById(\"y_coordinate\").innerText = "
                               " y_relative ; \n document.getElementById(\"speed\").innerText = speed; \n document.getElementById(\"angle\").innerText = angle; \n if(angle <0){ \n angle = 6.28 + parseFloat(angle);"
                               "  \n angle = angle.toFixed(1); \n } \n  \n if(speed <10) speed = 0; \n if(speed >99) speed = 99; \n cmd_speed = speed; \n cmd_angle = angle; \n  \n  \n } \n } \n  \n  \n function Send()"
                               " { \n $.get(\"http://000.000.000.000:80/\", {an:cmd_angle , sp:cmd_speed}); \n } \n  \n </script> \n  \n </body> \n </html><br>";

#endif
