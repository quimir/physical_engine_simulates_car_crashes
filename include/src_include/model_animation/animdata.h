/******************************************************************************
 * Copyright 2023 QuiMir
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file       animdata.h
 * @version 0.1
 *
 * @author     QuiMir<2546670299@qq.com>
 * @date       2023/11/20
 * @history
 *****************************************************************************/

#ifndef ANIMDATA_H
#define ANIMDATA_H

#include "src_include/geometricalias.h"

struct BoneInfo
{
    /**
     * @brief id Is index in finalBoneMatrices
     */
    int id;

    /**
     * @brief offset Matrix transforms vertex from model space to bone space
     */
    geometricalias::mat4 offset;
};

#endif // ANIMDATA_H
