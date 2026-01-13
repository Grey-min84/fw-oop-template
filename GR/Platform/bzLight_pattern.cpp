#include "bzLight_pattern.h"

/* *********************** 공용 패턴 ********************************** */
DoutPattNode_t g_xPattern_off   = {0,          UINT16_MAX, UINT8_MAX, &g_xPattern_off};
DoutPattNode_t g_xPattern_on    = {UINT16_MAX, 0,          UINT8_MAX, &g_xPattern_on};

DoutPattNode_t g_xPattern_welcome = {12, 12, 5, &g_xPattern_off};
DoutPattNode_t g_xPattern_modeChng  = {12, 12, 3, &g_xPattern_off};



DoutPattNode_t g_xPattern_DisconnGCM[2]= {
    {12, 12, 2, &g_xPattern_DisconnGCM[1]},
    {36, 36, 1, &g_xPattern_DisconnGCM[0]}
};
DoutPattNode_t g_xPattern_DisconnLidr[3]= {
    {36, 36, 1, &g_xPattern_DisconnLidr[1]},
    {12, 12, 2, &g_xPattern_DisconnLidr[2]},
    {24, 24, 1, &g_xPattern_DisconnLidr[0]}
};



