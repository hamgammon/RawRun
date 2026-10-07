#ifndef TRACKFACETOTAL_HPP
#define TRACKFACETOTAL_HPP

#include <gui_generated/containers/TrackFaceTotalBase.hpp>
#include <SDK/GUI/SensorStatusRow.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

/**
 * @brief Single activity screen for RawRun:
 *        1. GPS lock indicator
 *        2. Current time of day
 *        3. Elapsed run time
 */
class TrackFaceTotal : public TrackFaceTotalBase
{
public:
    TrackFaceTotal();
    virtual ~TrackFaceTotal() {}

    virtual void initialize();

    /** @brief Update GPS lock indicator state */
    void setGps(SDK::GUI::SensorStatusRow::State state);

    /** @brief Display current time of day */
    void setTime(uint8_t h, uint8_t m, bool is12Hour);

    /** @brief Display total elapsed run time as "H:MM:SS" */
    void setTimer(std::time_t sec);

    // Stubs for base interface compatibility
    void setPace(float pace) {}
    void setDistance(float dist, bool isImperial = false) {}

protected:
    SDK::GUI::SensorStatusRow mSensorRow;

    // Time of day label and value
    touchgfx::TextAreaWithOneWildcard mTimeLabel;
    static const uint16_t TIME_LABEL_SIZE = 16;
    touchgfx::Unicode::UnicodeChar mTimeLabelBuffer[TIME_LABEL_SIZE];

    touchgfx::TextAreaWithOneWildcard mDayTimeValue;
    static const uint16_t DAY_TIME_SIZE = 12;
    touchgfx::Unicode::UnicodeChar mDayTimeBuffer[DAY_TIME_SIZE];

    // AM/PM suffix for 12-hour format
    touchgfx::TextAreaWithOneWildcard mMeridiem;
    static const uint16_t MERIDIEM_SIZE = 4;
    touchgfx::Unicode::UnicodeChar mMeridiemBuffer[MERIDIEM_SIZE];

    // Elapsed run time label
    touchgfx::TextAreaWithOneWildcard mElapsedLabel;
    static const uint16_t ELAPSED_LABEL_SIZE = 16;
    touchgfx::Unicode::UnicodeChar mElapsedLabelBuffer[ELAPSED_LABEL_SIZE];

    static const int16_t kTimeY       = 62;
    static const int16_t kTimeH       = 44;
    static const int16_t kMeridiemY   = 80;
    static const int16_t kMeridiemH   = 22;
    static const int16_t kMeridiemGap = 4;
};

#endif // TRACKFACETOTAL_HPP
