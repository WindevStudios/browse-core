/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_PLAYLIST_PLAYLIST_UTIL_H_
#define BRAVE_COMPONENTS_PLAYLIST_PLAYLIST_UTIL_H_

#include <string>

#include "base/files/file_path.h"

namespace playlist {

std::string ConvertFilePathToUTF8(const base::FilePath& path);

}  // namespace playlist

#endif  // BRAVE_COMPONENTS_PLAYLIST_PLAYLIST_UTIL_H_