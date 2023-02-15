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

#include "directory_ex.h"
#include "hilog_wrapper.h"
#include "image_packer.h"
#include "pixel_map.h"
#include "wallpaper_manager.h"
#include "wallpaper_manager_kits.h"

constexpr int LOCKSCREEN = 1;
constexpr int HUNDRED = 100;
using namespace testing::ext;
using namespace testing;
using namespace OHOS::Media;
using namespace OHOS::HiviewDFX;
using namespace OHOS::MiscServices;

namespace OHOS {
namespace WallpaperMgrService {
constexpr const char *URI = "/data/test/theme/wallpaper/wallpaper_test.JPG";

class WallpaperPermissionTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
    static void CreateTempImage();
    static std::shared_ptr<PixelMap> CreateTempPixelMap();
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
    CreateTempImage();
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

void WallpaperPermissionTest::CreateTempImage()
{
    std::shared_ptr<PixelMap> pixelMap = CreateTempPixelMap();
    ImagePacker imagePacker;
    PackOption option;
    option.format = "image/jpeg";
    option.quality = HUNDRED;
    option.numberHint = 1;
    std::set<std::string> formats;
    imagePacker.GetSupportedFormats(formats);
    imagePacker.StartPacking(URI, option);
    HILOG_INFO("AddImage start");
    imagePacker.AddImage(*pixelMap);
    int64_t packedSize = 0;
    HILOG_INFO("FinalizePacking start");
    imagePacker.FinalizePacking(packedSize);
    if (packedSize == 0) {
        HILOG_INFO("FinalizePacking error");
    }
}

std::shared_ptr<PixelMap> WallpaperPermissionTest::CreateTempPixelMap()
{
    uint32_t color[100] = { 3, 7, 9, 9, 7, 6 };
    InitializationOptions opts = { { 5, 7 }, OHOS::Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<PixelMap> uniquePixelMap = PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<PixelMap> pixelMap = std::move(uniquePixelMap);
    return pixelMap;
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
    ErrorCode wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().ResetWallpaper(LOCKSCREEN);
    EXPECT_EQ(wallpaperErrorCode, E_NO_PERMISSION) << "throw permission error successfully";
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
    ErrorCode wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().GetFile(LOCKSCREEN, wallpaperFd);
    EXPECT_EQ(wallpaperErrorCode, E_NO_PERMISSION) << "throw permission error successfully";
}
/*********************   GetFile   *********************/

/*********************   GetPixelMap   *********************/
/**
* @tc.name:    GetPixelMapPermission001
* @tc.desc:    GetPixelMap with wallpaperType[1] throw permission error.
* @tc.type:    FUNC
* @tc.require: issueI60MT1
* @tc.author:  lvbai
*/
HWTEST_F(WallpaperPermissionTest, GetPixelMapPermission001, TestSize.Level0)
{
    HILOG_INFO("GetPixelMapPermission001  begin");
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
    ErrorCode wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().GetPixelMap(LOCKSCREEN, pixelMap);
    EXPECT_EQ(wallpaperErrorCode, E_NOT_SYSTEM_APP) << "throw permission error successfully";
}
/*********************   GetPixelMap   *********************/

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
    std::shared_ptr<PixelMap> pixelMap = WallpaperPermissionTest::CreateTempPixelMap();
    ErrorCode wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().SetWallpaper(pixelMap, 2);
    EXPECT_EQ(wallpaperErrorCode, E_NO_PERMISSION) << "throw permission error successfully";
}
/*********************   SetWallpaperByMap   *********************/

/*********************   SetWallpaperByUri   *********************/
/**
* @tc.name:    SetWallpaperByUriPermission001
* @tc.desc:    SetWallpaperByUri with wallpaperType[1] throw permission error.
* @tc.type:    FUNC
* @tc.require: issueI60MT1
* @tc.author:  lvbai
*/
HWTEST_F(WallpaperPermissionTest, SetWallpaperByUriPermission001, TestSize.Level0)
{
    HILOG_INFO("SetWallpaperByUriPermission001  begin");
    ErrorCode wallpaperErrorCode =
        OHOS::WallpaperMgrService::WallpaperManagerkits::GetInstance().SetWallpaper(URI, LOCKSCREEN);
    EXPECT_EQ(wallpaperErrorCode, E_NO_PERMISSION) << "throw permission error successfully";
    HILOG_INFO("SetWallpaperByUriPermission001  end");
}
/*********************   SetWallpaperByUri   *********************/
} // namespace WallpaperMgrService
} // namespace OHOS