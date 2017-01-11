#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#define NUM_ROBOTS 5
#define NUM_MISSIONS 9

#define SELECTABLE false
#define SELECTED true

#define NUM_OF_PATHS 512
#define MIN false  //TODO:could be dangerous
#define MAX true

bool const MATRIX_OF_PATHS[NUM_OF_PATHS][NUM_MISSIONS] = {
   {MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN},       //0
   {MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX},       //1
   {MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN},       //2
   {MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX},       //3
   {MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN},       //4
   {MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX},       //5
   {MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN},       //6
   {MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX},       //7
   {MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN},       //8
   {MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX},       //9
   {MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN},       //10
   {MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX},       //11
   {MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN},       //12
   {MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX},       //13
   {MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN},       //14
   {MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX},       //15
   {MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN},       //16
   {MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX},       //17
   {MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN},       //18
   {MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX},       //19
   {MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN},       //20
   {MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX},       //21
   {MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN},       //22
   {MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX},       //23
   {MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN},       //24
   {MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX},       //25
   {MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN},       //26
   {MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX},       //27
   {MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN},       //28
   {MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX},       //29
   {MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN},       //30
   {MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX},       //31
   {MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN},       //32
   {MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX},       //33
   {MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN},       //34
   {MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX},       //35
   {MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN},       //36
   {MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX},       //37
   {MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN},       //38
   {MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX},       //39
   {MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN},       //40
   {MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX},       //41
   {MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN},       //42
   {MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX},       //43
   {MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN},       //44
   {MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX},       //45
   {MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN},       //46
   {MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX},       //47
   {MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN},       //48
   {MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX},       //49
   {MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN},       //50
   {MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX},       //51
   {MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN},       //52
   {MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX},       //53
   {MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN},       //54
   {MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX},       //55
   {MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN},       //56
   {MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX},       //57
   {MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN},       //58
   {MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX},       //59
   {MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN},       //60
   {MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX},       //61
   {MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN},       //62
   {MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX},       //63
   {MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN},       //64
   {MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX},       //65
   {MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN},       //66
   {MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX},       //67
   {MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN},       //68
   {MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX},       //69
   {MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN},       //70
   {MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX},       //71
   {MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN},       //72
   {MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX},       //73
   {MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN},       //74
   {MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX},       //75
   {MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN},       //76
   {MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX},       //77
   {MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN},       //78
   {MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX},       //79
   {MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN},       //80
   {MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX},       //81
   {MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN},       //82
   {MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX},       //83
   {MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN},       //84
   {MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX},       //85
   {MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN},       //86
   {MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX},       //87
   {MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN},       //88
   {MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX},       //89
   {MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN},       //90
   {MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX},       //91
   {MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN},       //92
   {MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX},       //93
   {MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN},       //94
   {MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX},       //95
   {MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN},       //96
   {MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX},       //97
   {MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN},       //98
   {MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX},       //99
   {MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN},       //100
   {MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX},       //101
   {MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN},       //102
   {MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX},       //103
   {MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN},       //104
   {MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX},       //105
   {MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN},       //106
   {MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX},       //107
   {MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN},       //108
   {MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX},       //109
   {MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN},       //110
   {MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX},       //111
   {MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN},       //112
   {MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX},       //113
   {MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN},       //114
   {MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX},       //115
   {MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN},       //116
   {MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX},       //117
   {MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN},       //118
   {MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX},       //119
   {MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN},       //120
   {MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX},       //121
   {MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN},       //122
   {MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX},       //123
   {MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN},       //124
   {MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX},       //125
   {MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN},       //126
   {MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX},       //127
   {MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN},       //128
   {MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX},       //129
   {MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN},       //130
   {MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX},       //131
   {MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN},       //132
   {MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX},       //133
   {MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN},       //134
   {MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX},       //135
   {MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN},       //136
   {MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX},       //137
   {MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN},       //138
   {MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX},       //139
   {MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN},       //140
   {MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX},       //141
   {MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN},       //142
   {MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX},       //143
   {MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN},       //144
   {MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX},       //145
   {MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN},       //146
   {MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX},       //147
   {MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN},       //148
   {MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX},       //149
   {MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN},       //150
   {MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX},       //151
   {MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN},       //152
   {MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX},       //153
   {MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN},       //154
   {MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX},       //155
   {MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN},       //156
   {MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX},       //157
   {MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN},       //158
   {MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX},       //159
   {MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN},       //160
   {MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX},       //161
   {MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN},       //162
   {MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX},       //163
   {MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN},       //164
   {MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX},       //165
   {MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN},       //166
   {MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX},       //167
   {MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN},       //168
   {MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX},       //169
   {MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN},       //170
   {MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX},       //171
   {MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN},       //172
   {MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX},       //173
   {MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN},       //174
   {MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX},       //175
   {MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN},       //176
   {MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX},       //177
   {MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN},       //178
   {MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX},       //179
   {MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN},       //180
   {MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX},       //181
   {MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN},       //182
   {MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX},       //183
   {MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN},       //184
   {MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX},       //185
   {MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN},       //186
   {MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX},       //187
   {MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN},       //188
   {MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX},       //189
   {MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN},       //190
   {MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX},       //191
   {MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN},       //192
   {MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX},       //193
   {MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN},       //194
   {MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX},       //195
   {MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN},       //196
   {MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX},       //197
   {MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN},       //198
   {MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX},       //199
   {MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN},       //200
   {MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX},       //201
   {MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN},       //202
   {MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX},       //203
   {MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN},       //204
   {MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX},       //205
   {MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN},       //206
   {MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX},       //207
   {MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN},       //208
   {MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX},       //209
   {MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN},       //210
   {MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX},       //211
   {MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN},       //212
   {MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX},       //213
   {MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN},       //214
   {MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX},       //215
   {MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN},       //216
   {MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX},       //217
   {MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN},       //218
   {MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX},       //219
   {MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN},       //220
   {MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX},       //221
   {MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN},       //222
   {MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX},       //223
   {MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN},       //224
   {MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX},       //225
   {MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN},       //226
   {MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX},       //227
   {MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN},       //228
   {MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX},       //229
   {MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN},       //230
   {MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX},       //231
   {MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN},       //232
   {MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX},       //233
   {MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN},       //234
   {MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX},       //235
   {MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN},       //236
   {MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX},       //237
   {MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN},       //238
   {MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX},       //239
   {MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN},       //240
   {MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX},       //241
   {MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN},       //242
   {MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX},       //243
   {MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN},       //244
   {MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX},       //245
   {MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN},       //246
   {MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX},       //247
   {MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN},       //248
   {MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX},       //249
   {MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN},       //250
   {MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX},       //251
   {MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN},       //252
   {MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX},       //253
   {MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN},       //254
   {MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX},       //255
   {MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN},       //256
   {MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX},       //257
   {MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN},       //258
   {MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX},       //259
   {MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN},       //260
   {MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX},       //261
   {MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN},       //262
   {MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX},       //263
   {MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN},       //264
   {MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX},       //265
   {MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN},       //266
   {MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX},       //267
   {MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN},       //268
   {MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX},       //269
   {MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN},       //270
   {MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX},       //271
   {MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN},       //272
   {MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX},       //273
   {MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN},       //274
   {MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX},       //275
   {MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN},       //276
   {MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX},       //277
   {MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN},       //278
   {MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX},       //279
   {MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN},       //280
   {MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX},       //281
   {MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN},       //282
   {MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX},       //283
   {MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN},       //284
   {MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX},       //285
   {MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN},       //286
   {MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX},       //287
   {MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN},       //288
   {MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX},       //289
   {MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN},       //290
   {MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX},       //291
   {MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN},       //292
   {MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX},       //293
   {MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN},       //294
   {MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX},       //295
   {MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN},       //296
   {MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX},       //297
   {MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN},       //298
   {MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX},       //299
   {MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN},       //300
   {MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX},       //301
   {MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN},       //302
   {MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX},       //303
   {MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN},       //304
   {MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX},       //305
   {MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN},       //306
   {MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX},       //307
   {MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN},       //308
   {MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX},       //309
   {MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN},       //310
   {MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX},       //311
   {MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN},       //312
   {MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX},       //313
   {MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN},       //314
   {MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX},       //315
   {MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN},       //316
   {MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX},       //317
   {MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN},       //318
   {MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX},       //319
   {MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN},       //320
   {MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX},       //321
   {MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN},       //322
   {MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX},       //323
   {MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN},       //324
   {MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX},       //325
   {MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN},       //326
   {MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX},       //327
   {MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN},       //328
   {MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX},       //329
   {MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN},       //330
   {MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX},       //331
   {MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN},       //332
   {MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX},       //333
   {MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN},       //334
   {MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX},       //335
   {MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN},       //336
   {MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX},       //337
   {MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN},       //338
   {MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX},       //339
   {MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN},       //340
   {MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX},       //341
   {MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN},       //342
   {MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX},       //343
   {MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN},       //344
   {MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX},       //345
   {MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN},       //346
   {MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX},       //347
   {MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN},       //348
   {MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX},       //349
   {MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN},       //350
   {MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX},       //351
   {MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN},       //352
   {MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX},       //353
   {MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN},       //354
   {MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX},       //355
   {MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN},       //356
   {MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX},       //357
   {MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN},       //358
   {MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX},       //359
   {MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN},       //360
   {MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX},       //361
   {MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN},       //362
   {MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX},       //363
   {MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN},       //364
   {MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX},       //365
   {MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN},       //366
   {MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX},       //367
   {MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN},       //368
   {MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX},       //369
   {MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN},       //370
   {MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX},       //371
   {MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN},       //372
   {MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX},       //373
   {MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN},       //374
   {MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX},       //375
   {MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN},       //376
   {MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX},       //377
   {MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN},       //378
   {MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX},       //379
   {MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN},       //380
   {MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX},       //381
   {MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN},       //382
   {MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX},       //383
   {MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN},       //384
   {MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX},       //385
   {MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN},       //386
   {MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX},       //387
   {MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN},       //388
   {MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX},       //389
   {MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN},       //390
   {MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX},       //391
   {MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN},       //392
   {MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX},       //393
   {MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN},       //394
   {MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX},       //395
   {MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN},       //396
   {MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX},       //397
   {MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN},       //398
   {MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX},       //399
   {MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN},       //400
   {MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX},       //401
   {MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN},       //402
   {MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX},       //403
   {MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN},       //404
   {MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX},       //405
   {MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN},       //406
   {MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX},       //407
   {MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN},       //408
   {MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX},       //409
   {MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN},       //410
   {MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX},       //411
   {MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN},       //412
   {MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX},       //413
   {MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN},       //414
   {MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX},       //415
   {MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN},       //416
   {MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX},       //417
   {MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN},       //418
   {MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX},       //419
   {MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN},       //420
   {MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX},       //421
   {MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN},       //422
   {MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX},       //423
   {MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN},       //424
   {MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX},       //425
   {MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN},       //426
   {MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX},       //427
   {MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN},       //428
   {MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX},       //429
   {MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN},       //430
   {MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX},       //431
   {MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN},       //432
   {MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX},       //433
   {MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN},       //434
   {MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX},       //435
   {MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN},       //436
   {MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX},       //437
   {MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN},       //438
   {MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX},       //439
   {MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN},       //440
   {MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX},       //441
   {MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN},       //442
   {MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX},       //443
   {MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN},       //444
   {MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX},       //445
   {MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN},       //446
   {MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX},       //447
   {MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN},       //448
   {MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN,   MAX},       //449
   {MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MIN},       //450
   {MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX,   MAX},       //451
   {MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MIN},       //452
   {MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN,   MAX},       //453
   {MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MIN},       //454
   {MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX,   MAX},       //455
   {MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MIN},       //456
   {MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN,   MAX},       //457
   {MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MIN},       //458
   {MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX,   MAX},       //459
   {MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MIN},       //460
   {MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN,   MAX},       //461
   {MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MIN},       //462
   {MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX,   MAX},       //463
   {MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MIN},       //464
   {MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN,   MAX},       //465
   {MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MIN},       //466
   {MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX,   MAX},       //467
   {MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MIN},       //468
   {MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN,   MAX},       //469
   {MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MIN},       //470
   {MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX,   MAX},       //471
   {MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MIN},       //472
   {MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN,   MAX},       //473
   {MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MIN},       //474
   {MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX,   MAX},       //475
   {MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MIN},       //476
   {MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN,   MAX},       //477
   {MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MIN},       //478
   {MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX,   MAX},       //479
   {MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MIN},       //480
   {MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN,   MAX},       //481
   {MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MIN},       //482
   {MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX,   MAX},       //483
   {MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MIN},       //484
   {MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN,   MAX},       //485
   {MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MIN},       //486
   {MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX,   MAX},       //487
   {MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MIN},       //488
   {MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN,   MAX},       //489
   {MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MIN},       //490
   {MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX,   MAX},       //491
   {MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MIN},       //492
   {MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN,   MAX},       //493
   {MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MIN},       //494
   {MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX,   MAX},       //495
   {MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MIN},       //496
   {MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN,   MAX},       //497
   {MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MIN},       //498
   {MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX,   MAX},       //499
   {MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MIN},       //500
   {MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN,   MAX},       //501
   {MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MIN},       //502
   {MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX,   MAX},       //503
   {MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MIN},       //504
   {MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN,   MAX},       //505
   {MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MIN},       //506
   {MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX,   MAX},       //507
   {MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MIN},       //508
   {MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN,   MAX},       //509
   {MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MIN},       //510
   {MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX},       //511


};


float const MATRIX_TIMES_OFFLINE[NUM_MISSIONS][NUM_ROBOTS+NUM_MISSIONS] = {
	{112,   122,   191,   198,   122,   191,   191,   198,   122,   198,   122,   191,   198,    208},       //0
	{97,   108,   177,   184,   108,   177,   177,   184,   108,   184,   108,   177,   184,    193},        //1
	{96,   107,   168,   175,   107,   168,   168,   175,   107,   175,   107,   168,   175,    184},        //2
	{108,   121,   164,   172,   121,   164,   164,   172,   121,   172,   121,   164,   172,    181},       //3
	{116,   123,   175,   183,   123,   175,   175,   183,   123,   183,   123,   175,   183,    194},       //4
	{123,   109,   186,   194,   109,   186,   186,   194,   109,   194,   109,   186,   194,    204},       //5
	{135,   121,   198,   206,   121,   198,   198,   206,   121,   206,   121,   198,   206,    217},       //6
	{145,   131,   207,   216,   131,   207,   207,   216,   131,   216,   131,   207,   216,    226},       //7
	{157,   143,   220,   228,   143,   220,   220,   228,   143,   228,   143,   220,   228,    239},       //8

};

//R0 (0)|     112    |    97       |    96       |    108     |    116     |    123     |    135     |    145     |    157     |
//R1 (0)|     122    |    108     |    107     |    121     |    123     |    109     |    121     |    131     |    143     |
//R2 (0)|     191    |    177     |    168     |    164     |    175     |    186     |    198     |    207     |    220     |
//R3 (0)|     198    |    184     |    175     |    172     |    183     |    194     |    206     |    216     |    228     |
//R4 (0)|     208    |    193     |    184     |    181     |    194     |    204     |    217     |    226     |    239     |
//int const NUM_ROBOTS = 3;
//int const NUM_MISSIONS = 5;

//////////////////////////////////////////////

typedef struct{
    int id;
    int vertex;
}robot;

typedef struct{
    int id;
    int vertex;
}mission;

typedef struct{
    int robot;
    int mission;
    float initial_time;
    float mission_time;
}element;

typedef struct{
    element matrixOfElements[NUM_MISSIONS][NUM_ROBOTS+NUM_MISSIONS];
	std::vector<element> selectElements;
	
	bool selectedMissions[NUM_MISSIONS];
	bool selectedRobots[NUM_MISSIONS+NUM_ROBOTS];

	float l_min_time_miss_value[NUM_MISSIONS];	//array com o tempo mínimo
	int l_min_time_miss_robot[NUM_MISSIONS];			//array com o agv correspondente ao tempo mínimo

	float l_max_time_miss_value[NUM_MISSIONS];	//array com o tempo mínimo
	int l_max_time_miss_robot[NUM_MISSIONS];			//array com o agv correspondente ao tempo mínimo

	std::vector<element> l_minimumTime;
	std::vector<element> l_maximumTime;

}solution;


class heuristic_class
{
private:

    // int NUM_ROBOTS = 3;
    // int NUM_MISSIONS = 5;

  //  ros::NodeHandlePtr node_handle_;
  //  ros::ServiceClient client_;

    std::vector<robot> l_robots;
    std::vector<mission> l_missions;
    solution initial_solution;

	float offlineTime;
	element selectedElement;

	int currIteration;


public:

	heuristic_class(void);
	~heuristic_class(void);

  //  void setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle);

	//float getTEAstarOnline(int robot, int vertex_origin, int vertex_end);
	float getTEAstarOffline(int robot, int vertex_origin, int vertex_end);
    void initializeListOfRobots(void);
    void initializeListOfMissions(void);
    void solutionInitialSetup(void);
    void printSolutionTable(void);
	int getNextTime(void);
	void addElementAtEnd(int end_position, float mission_time);
	
	//####
	bool missionIsSelectable(int mission);
	bool missionIsSelected(int mission);
	bool robotIsSelectable(int robot);
	bool robotIsSelected(int robot);
	//####

	void updateMaximumTime(void);
	void updateMinimumTime(void);
	void printMaximumArray(void);
	void printMinimumArray(void);

	float getMinimumOfMinimum(void);
	float getMinimumOfMaximum(void);
	float getMaximumOfMinimum(void);
	float getMaximumOfMaximum(void);
	//####

	int getRemainingMissions(void);
	int getMaxResult(void);
	
	int selectTime(void);

	void printResults(void);


	//####
	void runHeuristic1(int path);

};
