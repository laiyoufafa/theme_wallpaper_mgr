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
#ifndef WALLPAPER_SERVICES_WALLPAPER_COMMON_H
#define WALLPAPER_SERVICES_WALLPAPER_COMMON_H

#include <string>
#include "errors.h"

namespace OHOS {
namespace WallpaperMgrService {
#define WALLPAPER_SERVICE_NAME "WallpaperMgrService"
static const std::string WALLPAPER_BUNDLE_NAME = "ohos";
static const std::string WALLPAPER_PERMISSION_NAME_GET_WALLPAPER = "ohos.permission.GET_WALLPAPER";
static const std::string WALLPAPER_PERMISSION_NAME_SET_WALLPAPER = "ohos.permission.SET_WALLPAPER";
static const std::string WALLPAPER_PERMISSION_NAME_READ_USER_STORAGE = "ohos.permission.READ_MEDIA";
static const std::string WALLPAPER_PERMISSION_NAME_CAPTURE_SCREEN = "ohos.permission.CAPTURE_SCREEN";

static const std::string TEST_LABEL = "test label";
static const std::string TEST_DESCRIPTION = "test description";

static const int TEST_LABEL_ID = 9527;
static const int TEST_DESCRIPTION_ID = 9528;
static const int TEST_INVALID_USER_ID = -1;
static const int TEST_USER_ID = 0;
static const int TEST_SUB_USER_ID = 10;

enum WallpaperModule {
    WALLPAPER_MODULE_SERVICE_ID = 0x07,
};
// time error offset, used only in this file.
constexpr ErrCode WALLPAPER_ERR_OFFSET = ErrCodeOffset(SUBSYS_SMALLSERVICES, WALLPAPER_MODULE_SERVICE_ID);

enum WallpaperError {
    E_WALLPAPER_OK = WALLPAPER_ERR_OFFSET,
    E_WALLPAPER_SA_DIED,
    E_WALLPAPER_READ_PARCEL_ERROR,
    E_WALLPAPER_WRITE_PARCEL_ERROR,
    E_WALLPAPER_PUBLISH_FAIL,
    E_WALLPAPER_TRANSACT_ERROR,
    E_WALLPAPER_DEAL_FAILED,
    E_WALLPAPER_PARAMETERS_INVALID,
    E_WALLPAPER_SET_RTC_FAILED,
    E_WALLPAPER_NOT_FOUND,
    E_WALLPAPER_NO_PERMISSION,
};
} // namespace
} // names

#endif // WALLPAPER_SERVICES_WALLPAPER_COMMON_H
