/**
 * Copyright 2014 (c) Baidu, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */

#include "bcesdk/model/json_response.h"
#include "bcesdk/util/util.h"
#include <json/json.h>
BEGIN_CPPSDK_NAMESPACE

void JsonResponse::do_handle_chain(HttpResponse &) {
    LOG(DEBUG) << "response body: " << _buffer;
    Json::Reader reader;
    Json::Value value;
    if (!reader.parse(_buffer, value)) {
        LOG(ERROR) << "parse response fail";
        set_error(STATUS_INVALID_RESPONSE, "MalformedJson");
        return;
    }
    try {
        deserialize(value);
    } catch (...) {
        LOG(ERROR) << "invalid response json content: " <<  _buffer;
        set_error(STATUS_INVALID_RESPONSE, "InvalidContent");
    }
}

END_CPPSDK_NAMESPACE

