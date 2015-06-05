/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2015 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#include "DefaultFonts.hpp"
#include "AutoFont.hpp"
#include "GlobalFonts.hpp"
#include "FontSettings.hpp"
#include "StandardFonts.hpp"
#include "Hardware/DisplayDPI.hpp"
#include "Screen/Font.hpp"
#include "Screen/Layout.hpp"

#ifdef HAVE_TEXT_CACHE
#include "Screen/Custom/Cache.hpp"
#endif

#include <algorithm>

#include <string.h>

#ifdef WIN32

static void
LoadAltairLogFonts(FontSettings &settings)
{
  settings.dialog = FontDescription(_T("RasterGothicTwelveCond"), 13);
#ifdef GNAV
  settings.dialog_small = FontDescription(_T("RasterGothicNineCond"), 10);
#endif
  settings.cdi = FontDescription(_T("RasterGothicEighteenCond"), 19, true);
  settings.map = FontDescription(_T("RasterGothicFourteenCond"), 15);
  settings.map_bold = FontDescription(_T("RasterGothicFourteenCond"),
                                      15, true);
  settings.monospace = FontDescription(GetStandardMonospaceFontFace(),
                                       12, false, false, true);
}

#endif

static void
InitialiseLogFonts(FontSettings &settings)
{
#ifdef WIN32
  if (IsAltair()) {
    LoadAltairLogFonts(settings);
    return;
  }
#endif

  settings.dialog = FontDescription(std::min(Layout::FontScale(12),
                                             Layout::min_screen_pixels / 20));

  // new font for CDI Scale
  settings.cdi = FontDescription(Layout::FontScale(10),
                                 false, false, true);

  // new font for map labels
  settings.map = FontDescription(Layout::FontScale(10));

  // Font for map bold text
  settings.map_bold = FontDescription(Layout::FontScale(10), true);

  settings.monospace = FontDescription(settings.dialog.GetHeight(),
                                       false, false, true);
}

FontSettings
Fonts::GetDefaults()
{
  FontSettings settings;
  InitialiseLogFonts(settings);
  return settings;
}

bool
Fonts::Initialize()
{
  const auto default_settings = GetDefaults();

  return Load(default_settings);
}
