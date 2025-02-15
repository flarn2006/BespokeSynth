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
//
//  Pumper.h
//  modularSynth
//
//  Created by Ryan Challinor on 3/16/13.
//
//

#ifndef __modularSynth__Pumper__
#define __modularSynth__Pumper__

#include <iostream>
#include "IAudioEffect.h"
#include "Checkbox.h"
#include "Slider.h"
#include "DropdownList.h"
#include "LFO.h"

class Pumper : public IAudioEffect, public IDropdownListener, public IFloatSliderListener
{
public:
   Pumper();
   virtual ~Pumper();

   static IAudioEffect* Create() { return new Pumper(); }


   void CreateUIControls() override;

   //IAudioEffect
   void ProcessAudio(double time, ChannelBuffer* buffer) override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   float GetEffectAmount() override;
   std::string GetType() override { return "pumper"; }

   void DropdownUpdated(DropdownList* list, int oldVal) override;
   void CheckboxUpdated(Checkbox* checkbox) override {}
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override;

   void SaveState(FileStreamOut& out) override;
   void LoadState(FileStreamIn& in, int rev) override;
   int GetModuleSaveStateRev() const override { return 1; }

private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& w, float& h) override
   {
      w = mWidth;
      h = mHeight;
   }
   bool Enabled() const override { return mEnabled; }
   double GetIntervalPos(double time);
   void SyncToAdsr();

   FloatSlider* mAmountSlider;
   FloatSlider* mLengthSlider;
   FloatSlider* mCurveSlider;
   FloatSlider* mAttackSlider;

   ::ADSR mAdsr;
   NoteInterval mInterval;
   DropdownList* mIntervalSelector;
   float mLastValue;
   float mAmount;
   float mLength;
   float mAttack;

   float mWidth;
   float mHeight;
};

#endif /* defined(__modularSynth__Pumper__) */
