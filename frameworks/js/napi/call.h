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
#ifndef WALLPAPER_CALL_H
#define WALLPAPER_CALL_H

#include <functional>
#include <memory>

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

namespace OHOS::WallpaperNAPI {
class Call final {
public:
    class Context {
    public:
        using InputAction = std::function<napi_status(napi_env, size_t, napi_value *, napi_value)>;
        using OutputAction = std::function<napi_status(napi_env, napi_value *)>;
        using ExecAction = std::function<void(Context *)>;
        Context(InputAction input, OutputAction output) : input_(std::move(input)), output_(std::move(output)){};
        virtual ~Context(){};
        void SetAction(InputAction input, OutputAction output = nullptr)
        {
            input_ = input;
            output_ = output;
        }

        void SetExecution(ExecAction exec)
        {
            exec_ = exec;
        }

        void SetErrInfo(int32_t errCode, std::string errMsg)
        {
            errCode_ = errCode;
            errMsg_ = errMsg;
        }

        virtual napi_status operator()(napi_env env, size_t argc, napi_value *argv, napi_value self)
        {
            if (input_ == nullptr) {
                return napi_ok;
            }
            auto ret = input_(env, argc, argv, self);
            input_ = nullptr;
            return ret;
        }

        virtual napi_status operator()(napi_env env, napi_value *result)
        {
            if (output_ == nullptr) {
                *result = nullptr;
                return napi_ok;
            }
            auto ret = output_(env, result);
            output_ = nullptr;
            return ret;
        }

        virtual void Exec()
        {
            if (exec_ == nullptr) {
                return;
            }
            exec_(this);
            exec_ = nullptr;
        };

    protected:
        friend class Call;
        InputAction input_ = nullptr;
        OutputAction output_ = nullptr;
        ExecAction exec_ = nullptr;
        int32_t errCode_ = 0;
        std::string errMsg_;
    };

    // The default AsyncCallback in the parameters is at the end position.
    static constexpr size_t ASYNC_DEFAULT_POS = -1;
    Call(napi_env env, napi_callback_info info, std::shared_ptr<Context> context, size_t pos = ASYNC_DEFAULT_POS,
        bool needException = true);
    ~Call();
    napi_value AsyncCall(napi_env env, const std::string &resourceName = "AsyncCall");
    napi_value SyncCall(napi_env env);

private:
    enum Arg : int32_t { ARG_ERROR, ARG_DATA, ARG_BUTT };
    struct CallContext {
        std::shared_ptr<Context> ctx = nullptr;
        napi_ref callback = nullptr;
        napi_ref self = nullptr;
        napi_deferred defer = nullptr;
        napi_async_work work = nullptr;
    };
    static void OnExecute(napi_env env, void *data);
    static void OnComplete(napi_env env, napi_status status, void *data);
    static void DeleteContext(napi_env env, CallContext *context);

    CallContext *context_ = nullptr;
    napi_env env_ = nullptr;
};
} // namespace OHOS::WallpaperNAPI

#endif // WALLPAPER_CALL_H
