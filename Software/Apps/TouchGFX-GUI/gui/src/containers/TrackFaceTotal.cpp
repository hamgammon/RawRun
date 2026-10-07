#include <gui/containers/TrackFaceTotal.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include "SDK/Utils/ClockTime.hpp"
#include "SDK/Utils/Utils.hpp"

TrackFaceTotal::TrackFaceTotal()
{
}

void TrackFaceTotal::initialize()
{
    TrackFaceTotalBase::initialize();

    // Hide unused widgets from base
    paceText.setVisible(false);
    paceValue.setVisible(false);
    distanceText.setVisible(false);
    distanceValue.setVisible(false);
    distanceUnits.setVisible(false);
    line1.setVisible(false);
    timerText.setVisible(false);

    // 1. GPS lock indicator at top
    add(mSensorRow);
    mSensorRow.setPosition(0, 16, 240, 24);
    mSensorRow.setIcons(BITMAP_SENSORGPSDARK_ID, BITMAP_SENSORGPSLIGHT_ID,
                        BITMAP_INVALID, BITMAP_INVALID);
    mSensorRow.setGps(SDK::GUI::SensorStatusRow::State::Searching);

    // 2. Current Time Section
    // Label "TIME"
    mTimeLabel.setPosition(0, 44, 240, 18);
    mTimeLabel.setColor(touchgfx::Color::getColorFromRGB(140, 140, 140));
    mTimeLabel.setLinespacing(0);
    mTimeLabel.setTypedText(touchgfx::TypedText(T_TMP_REGULAR_14));
    Unicode::snprintf(mTimeLabelBuffer, TIME_LABEL_SIZE, "TIME");
    mTimeLabel.setWildcard(mTimeLabelBuffer);
    add(mTimeLabel);

    // Time value (SemiBold 40)
    mDayTimeValue.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    mDayTimeValue.setLinespacing(0);
    mDayTimeValue.setTypedText(touchgfx::TypedText(T_TMP_SEMIBOLD_40_L));
    Unicode::snprintf(mDayTimeBuffer, DAY_TIME_SIZE, "0:00");
    mDayTimeValue.setWildcard(mDayTimeBuffer);
    add(mDayTimeValue);

    // AM/PM suffix (12h format only)
    mMeridiem.setColor(touchgfx::Color::getColorFromRGB(160, 160, 160));
    mMeridiem.setLinespacing(0);
    mMeridiem.setTypedText(touchgfx::TypedText(T_TMP_MEDIUM_18_L));
    mMeridiem.setWildcard(mMeridiemBuffer);
    mMeridiem.setVisible(false);
    add(mMeridiem);

    // Central teal divider line
    line2.setPosition(35, 118, 170, 3);
    line2.setVisible(true);

    // 3. Elapsed Run Time Section
    // Label "ELAPSED"
    mElapsedLabel.setPosition(0, 130, 240, 18);
    mElapsedLabel.setColor(touchgfx::Color::getColorFromRGB(140, 140, 140));
    mElapsedLabel.setLinespacing(0);
    mElapsedLabel.setTypedText(touchgfx::TypedText(T_TMP_REGULAR_14));
    Unicode::snprintf(mElapsedLabelBuffer, ELAPSED_LABEL_SIZE, "ELAPSED");
    mElapsedLabel.setWildcard(mElapsedLabelBuffer);
    add(mElapsedLabel);

    // Elapsed timer value
    timerValue.setPosition(0, 152, 240, 42);
    timerValue.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    timerValue.setLinespacing(0);
    timerValue.setTypedText(touchgfx::TypedText(T_TMP_SEMIBOLD_35));
    Unicode::snprintf(timerValueBuffer, TIMERVALUE_SIZE, "0:00:00");
    timerValue.setWildcard(timerValueBuffer);
    timerValue.setVisible(true);
}

void TrackFaceTotal::setGps(SDK::GUI::SensorStatusRow::State state)
{
    mSensorRow.setGps(state);
}

void TrackFaceTotal::setTime(uint8_t h, uint8_t m, bool is12Hour)
{
    mDayTimeValue.invalidate();
    mMeridiem.invalidate();

    const SDK::Clock::Hour12 civil = SDK::Clock::to12Hour(h);
    const uint8_t hour = is12Hour ? civil.hour : h;
    const bool    pm   = civil.pm;

    Unicode::snprintf(mDayTimeBuffer, DAY_TIME_SIZE, "%u:%02u", hour, m);
    mDayTimeValue.setWildcard(mDayTimeBuffer);
    const uint16_t timeW = mDayTimeValue.getTextWidth();

    uint16_t merW   = 0;
    uint16_t groupW = timeW;
    if (is12Hour) {
        mMeridiemBuffer[0] = pm ? 'P' : 'A';
        mMeridiemBuffer[1] = 'M';
        mMeridiemBuffer[2] = 0;
        mMeridiem.setWildcard(mMeridiemBuffer);
        merW   = mMeridiem.getTextWidth();
        groupW = static_cast<uint16_t>(timeW + kMeridiemGap + merW);
    }

    const int16_t groupLeft = static_cast<int16_t>((getWidth() - groupW) / 2);
    mDayTimeValue.setPosition(groupLeft, kTimeY, static_cast<int16_t>(timeW + 4), kTimeH);
    mDayTimeValue.invalidate();

    if (is12Hour) {
        mMeridiem.setPosition(static_cast<int16_t>(groupLeft + timeW + kMeridiemGap),
                              kMeridiemY, static_cast<int16_t>(merW + 4), kMeridiemH);
        mMeridiem.setVisible(true);
        mMeridiem.invalidate();
    } else {
        mMeridiem.setVisible(false);
    }
}

void TrackFaceTotal::setTimer(std::time_t sec)
{
    auto hms = SDK::Utils::toHMS(sec);
    Unicode::snprintf(timerValueBuffer, TIMERVALUE_SIZE,
        "%u:%02u:%02u", hms.h, hms.m, hms.s);
    timerValue.invalidate();
}
