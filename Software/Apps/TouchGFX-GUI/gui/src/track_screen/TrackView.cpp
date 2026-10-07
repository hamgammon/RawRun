#include <gui/track_screen/TrackView.hpp>

TrackView::TrackView()
{
}

void TrackView::setupScreen()
{
    TrackViewBase::setupScreen();

    // In single-screen mode, L1/L2 face scrolling is disabled.
    // R1 provides access to the Pause/Stop/Resume action menu.
    buttons.setL1(Buttons::NONE);
    buttons.setL2(Buttons::NONE);
    buttons.setR1(Buttons::AMBER);
    buttons.setR2(Buttons::NONE);

    // Hide scroll indicator and all other faces
    scrollIndicator.setVisible(false);
    trackFaceIntervals.setVisible(false);
    trackFaceLap.setVisible(false);
    trackFaceStatus.setVisible(false);

    // Show the single main activity screen
    trackFaceTotal.setVisible(true);
}

void TrackView::tearDownScreen()
{
    TrackViewBase::tearDownScreen();
}

void TrackView::setIntervalsMode(bool /*mode*/)
{
    scrollIndicator.setVisible(false);
}

void TrackView::setPositionId(uint16_t /*id*/)
{
    // Pin to the single screen
    trackFaceIntervals.setVisible(false);
    trackFaceLap.setVisible(false);
    trackFaceStatus.setVisible(false);
    trackFaceTotal.setVisible(true);
    scrollIndicator.setVisible(false);
    trackFaceTotal.invalidate();
}

uint16_t TrackView::getPositionId()
{
    return 1;
}

void TrackView::setConfig(bool /*isImperial*/, const uint8_t* /*thresholds*/, uint8_t /*thresholdCount*/)
{
}

void TrackView::setTimeFormat(bool is12Hour)
{
    mIs12Hour = is12Hour;
}

void TrackView::setTrackData(const Track::Data& data)
{
    trackFaceTotal.setTimer(data.totalTime);
}

void TrackView::setTime(uint8_t h, uint8_t m)
{
    trackFaceTotal.setTime(h, m, mIs12Hour);
}

void TrackView::setBatteryLevel(uint8_t /*level*/)
{
}

void TrackView::setGpsFix(bool state)
{
    trackFaceTotal.setGps(SDK::GUI::SensorStatusRow::gpsState(state));
}

void TrackView::setAccessoryStatus(uint8_t /*state*/)
{
}

void TrackView::handleKeyEvent(uint8_t key)
{
    if (key == SDK::GUI::Button::R1) {
        application().gotoTrackActionScreenNoTransition();
    }
}
