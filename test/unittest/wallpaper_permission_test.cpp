/*
* Copyright (C) 2022 Huawei Device Co., Ltd.
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

#include <ctime>
#include <gtest/gtest.h>

#include "accesstoken_kit.h"
#include "directory_ex.h"
#include "hilog_wrapper.h"
#include "nativetoken_kit.h"
#include "pixel_map.h"
#include "token_setproc.h"
#include "wallpaper_manager.h"
#include "wallpaper_manager_kits.h"

constexpr int LOCKSCREEN = 1;
using namespace testing::ext;
using namespace testing;
using namespace OHOS::Media;
using namespace OHOS::HiviewDFX;
using namespace OHOS::MiscServices;
using namespace OHOS::Security::AccessToken;

namespace OHOS {
namespace WallpaperMgrService {
constexpr const char *URL = "/system/etc/wallpaper_test.JPG";

class WallpaperPermissionTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
};
const std::string VALID_SCHEMA_STRICT_DEFINE = "{\"SCHEMA_VERSION\":\"1.0\","
                                               "\"SCHEMA_MODE\":\"STRICT\","
                                               "\"SCHEMA_SKIPSIZE\":0,"
                                               "\"SCHEMA_DEFINE\":{"
                                               "\"age\":\"INTEGER, NOT NULL\""
                                               "},"
                                               "\"SCHEMA_INDEXES\":[\"$.age\"]}";

void WallpaperPermissionTest::SetUpTestCase(void)
{
    HILOG_INFO("SetUpPermissionTestCase");
}

void WallpaperPermissionTest::TearDownTestCase(void)
{
    HILOG_INFO("PermissionTestTearDownTestCase");
}

void WallpaperPermissionTest::SetUp(void)
{
}

void WallpaperPermissionTest::TearDown(void)
{
}

/*********************   ResetWallpaper   *********************/
/**
* @tc.name:    ResetPermission001
* @tc.desc:    Reset wallpaper throw permission error.
* @tc.type:    FUNC
* @tc.require: issueI60MT1
* @tc.author:  lvbai
*/
HWTEST_F(WallpaperPermissionTest, ResetPermission001, TestSize.Level1)
{
    HILOG_INFO("ResetPermission001 begin");
    int wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().ResetWallpaper(LOCKSCREEN);
    EXPECT_EQ(wallpaperErrorCode, static_cast<int32_t>(E_NO_PERMISSION)) << "throw permission error successfully";
}
/*********************   ResetWallpaper   *********************/

/*********************   GetFile   *********************/
/**
* @tc.name:    GetFilePermission001
* @tc.desc:    GetFile with wallpaperType[1] throw permission error.
* @tc.type:    FUNC
* @tc.require: issueI60MT1
* @tc.author:  lvbai
*/
HWTEST_F(WallpaperPermissionTest, GetFilePermission001, TestSize.Level0)
{
    HILOG_INFO("GetFilePermission001 begin");
    int32_t wallpaperFd = 0;
    int wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().GetFile(LOCKSCREEN, wallpaperFd);
    EXPECT_EQ(wallpaperErrorCode, static_cast<int32_t>(E_NO_PERMISSION)) << "throw permission error successfully";
}
/*********************   GetFile   *********************/

/*********************   GetPiexlMap   *********************/
/**
* @tc.name:    GetPiexlMapPermission001
* @tc.desc:    GetPixelMap with wallpaperType[1] throw permission error.
* @tc.type:    FUNC
* @tc.require: issueI60MT1
* @tc.author:  lvbai
*/
HWTEST_F(WallpaperPermissionTest, GetPiexlMapPermission001, TestSize.Level0)
{
    HILOG_INFO("GetPiexlMapPermission001  begin");
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
    int32_t wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().GetPixelMap(LOCKSCREEN, pixelMap);
    EXPECT_EQ(wallpaperErrorCode, static_cast<int32_t>(E_NO_PERMISSION)) << "throw permission error successfully";
}
/*********************   GetPiexlMap   *********************/

/*********************   SetWallpaperByMap   *********************/
/**
* @tc.name:    SetWallpaperByMapPermission001
* @tc.desc:    SetWallpaperByMap with wallpaperType[1] throw permission error.
* @tc.type:    FUNC
* @tc.require: issueI60MT1
* @tc.author:  lvbai
*/
HWTEST_F(WallpaperPermissionTest, SetWallpaperByMapPermission001, TestSize.Level0)
{
    HILOG_INFO("SetWallpaperByMapPermission001  begin");
    uint32_t color[100] = { 3, 7, 9, 9, 7, 6 };
    InitializationOptions opts = { { 5, 7 }, OHOS::Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<PixelMap> pixelMap = PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    int32_t wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().SetWallpaper(pixelMap, 2);
    EXPECT_EQ(wallpaperErrorCode, static_cast<int32_t>(E_NO_PERMISSION)) << "throw permission error successfully";
}
/*********************   SetWallpaperByMap   *********************/

/*********************   SetWallpaperByUrl   *********************/
/**
* @tc.name:    SetWallpaperByUrlPermission001
* @tc.desc:    SetWallpaperByUrl with wallpaperType[1] throw permission error.
* @tc.type:    FUNC
* @tc.require: issueI60MT1
* @tc.author:  lvbai
*/
HWTEST_F(WallpaperPermissionTest, SetWallpaperByUrlPermission001, TestSize.Level0)
{
    HILOG_INFO("SetWallpaperByUrlPermission001  begin");
    int32_t wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().SetWallpaper(URL, LOCKSCREEN);
    EXPECT_EQ(wallpaperErrorCode, static_cast<int32_t>(E_NO_PERMISSION)) << "throw permission error successfully";
}
/*********************   SetWallpaperByUrl   *********************/
} // namespace WallpaperMgrService
} // namespace OHOS