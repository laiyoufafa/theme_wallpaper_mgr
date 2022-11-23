/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "WallpaperColorChangeListenerProxy"

#include "hilog_wrapper.h"
#include "message_parcel.h"
#include "wallpaper_color_change_listener_proxy.h"

namespace OHOS {
namespace WallpaperMgrService {
using namespace std::chrono;

void WallpaperColorChangeListenerProxy::OnColorsChange(const std::vector<RgbaColor> &color, int wallpaperType)
{
    HILOG_DEBUG("WallpaperColorChangeListenerProxy::OnColorsChange Start");
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(WallpaperColorChangeListenerProxy::GetDescriptor())) {
        HILOG_ERROR("write descriptor failed");
        return;
    }

    unsigned int size = color.size();
    if (!data.WriteInt32(size)) {
        HILOG_ERROR("write color size failed");
        return;
    }
    for (unsigned int i = 0; i < size; ++i) {
        if (!(data.WriteInt32(color[i].red) && data.WriteInt32(color[i].green) && data.WriteInt32(color[i].blue)
                && data.WriteInt32(color[i].alpha))) {
            HILOG_ERROR("write color failed");
            return;
        }
    }

    if (!data.WriteInt32(wallpaperType)) {
        HILOG_ERROR("write wallpaperType failed");
        return;
    }

    int error = Remote()->SendRequest(ONCOLORSCHANGE, data, reply, option);
    if (error != 0) {
        HILOG_ERROR("SendRequest failed, error %{public}d", error);
    }
    HILOG_DEBUG("WallpaperColorChangeListenerProxy::OnColorsChange End");
}
}  // namespace WallpaperMgrService
}  // namespace OHOS
