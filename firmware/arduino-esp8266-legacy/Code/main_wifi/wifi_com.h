// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#ifndef WIFI_COM_H
#define WIFI_COM_H

#include <Arduino.h>

#define NW_SSID \"YOUR_WIFI_SSID\"
#define NW_PASS \"YOUR_WIFI_PASSWORD\"

void wifi_init();

int get_cmd();

#endif
