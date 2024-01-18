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

#ifndef RENDER_RENDERTIMER_H
#define RENDER_RENDERTIMER_H

#include <QObject>
#include <QElapsedTimer>

class RenderTimer : public QObject
{
    Q_OBJECT
public:
    RenderTimer();

    void Start();

    void Stop();

    qint64 ElapsedTime()const;

    double ElapsedTimeInMilliseconds()const;

    inline qint64 GetStartTime()const
    {
        return this->start_time_;
    }

    inline qint64 GetEndTime()const
    {
        return this->end_time_;
    }

private:
    QElapsedTimer timer_;
    qint64 start_time_;
    qint64 end_time_;
};

#endif // RENDER_RENDERTIMER_H
