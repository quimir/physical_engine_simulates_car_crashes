/**
 ** This file is part of the physical_engine_simulates_car_crashes project.
 ** Copyright 2024 QuiMir <2546670299@qq.com>.
 **
 ** Licensed under the Apache License, Version 2.0 (the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 **
 ** http://www.apache.org/licenses/LICENSE-2.0
 **
 ** Unless required by applicable law or agreed to in writing, software
 ** distributed under the License is distributed on an "AS IS" BASIS,
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 **/

#include "src_include/render/render_timer.h"
#include "src_include/file_system/file_write_system.h"

RenderTimer::RenderTimer()
{
    this->timer_.start();
}

void RenderTimer::Start()
{
    this->start_time_=this->timer_.nsecsElapsed();
}

void RenderTimer::Stop()
{
    this->end_time_=this->timer_.nsecsElapsed();
}

qint64 RenderTimer::ElapsedTime() const
{
    if(0==this->end_time_)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            "endTime not set. Returning 0 milliseconds.");
        return 0.0;
    }

    return this->end_time_-this->start_time_;
}

double RenderTimer::ElapsedTimeInMilliseconds() const
{
    if(0==this->end_time_)
    {
        FileWriteSystem::GetInstance().OutMessage(
            FileWriteSystem::MessageTypeBit::kDebug,
            "endTime not set. Returning 0 milliseconds.");
        return 0.0;
    }

    return static_cast<double>(ElapsedTime())/ 1000000.0;
}
