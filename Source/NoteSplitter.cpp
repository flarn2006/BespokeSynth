// vim: ts=3:expandtab
/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
/*
  ==============================================================================

    NoteSplitter.h
    Created: 1 Sep 2022 6:03:34pm
    Author:  Sara Sparks

  ==============================================================================
*/

#include "NoteSplitter.h"
#include "OpenFrameworksPort.h"
#include "Scale.h"
#include "ModularSynth.h"

NoteSplitter::NoteSplitter()
: mPitch(60)
, mPitchSlider(nullptr)
{
}

void NoteSplitter::CreateUIControls()
{
   IDrawableModule::CreateUIControls();
   mPitchSlider = new IntSlider(this, "pitch", 4, 2, 100, 15, &mPitch, 0, 127);
}

void NoteSplitter::DrawModule()
{
   if (Minimized() || IsVisible() == false)
      return;

   mPitchSlider->Draw();
}

void NoteSplitter::PlayNote(double time, int pitch, int velocity, int voiceIdx, ModulationParameters modulation)
{
   if (mEnabled && velocity > 0)
   {
      ComputeSliders(0);
      PlayNoteOutput(time, pitch, velocity, voiceIdx, modulation);
   }
}

void NoteSplitter::LoadLayout(const ofxJSONElement& moduleInfo)
{
   mModuleSaveData.LoadString("target", moduleInfo);

   SetUpFromSaveData();
}

void NoteSplitter::SetUpFromSaveData()
{
   SetUpPatchCables(mModuleSaveData.GetString("target"));
}
