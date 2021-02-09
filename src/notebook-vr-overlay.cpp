#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <openvr.h>
#include "MathUtils.h"

using namespace vr;

IVRSystem* vr_context;

int init_ovr() {
	if (VR_IsHmdPresent()) {
		std::cout << "An HMD was successfully found in the system" << std::endl;

		if (VR_IsRuntimeInstalled()) {
			char runtime_path[] = "somewhere";
			// VR_GetRuntimePath(&runtime_path);
			std::cout << "Runtime correctly installed at '" << runtime_path << "'" << std::endl;
		}
		else {
			std::cout << "Runtime was not found, quitting app" << std::endl;
			return -1;
		}
	}
	else {
		std::cout << "An HMD was not found, quitting app" << std::endl;
		return -1;
	}

	vr::HmdError err;
	vr_context = vr::VR_Init(&err, vr::VRApplication_Overlay);
	vr_context == NULL
		? std::cout << "Error while initializing SteamVR runtime. Error code is " << vr::VR_GetVRInitErrorAsSymbol(err) << std::endl
		: std::cout << "SteamVR runtime successfully initialized" << std::endl;

	return  0;
}

void logTrackedDevices() {
	TrackedDeviceClass currentClass;

	for (int i = 0; i < k_unMaxTrackedDeviceCount; i++) {
		currentClass = vr_context->GetTrackedDeviceClass(i);
		if (currentClass != TrackedDeviceClass_Invalid) {
			std::cout << "Found Tracked device id(" << i << ") with class: " << currentClass << std::endl;
		}
	}
}

int main() {
	// Future Steps:
	// 1. Make sure I can build a project with the openvr library. (Done)
	// 2. Create a basic openvr overlay that renders... anything. (Done)
	// 3. Get input from the user so they can interact with the overlay.
	// 4. Allow the user to draw on the overlay.
	// 5. Allow the user to save and manage drawn notes.
	std::cout << "OVR overlay version: " << vr::IVROverlay_Version << std::endl;

	char overlayKey[] = "me.yukiironite.notebook_overlay";
	char overlayName[] = "Notebook Overlay";
	VROverlayHandle_t overlayHandle;

	init_ovr();

	VROverlay()->CreateOverlay(overlayKey, overlayName, &overlayHandle);
	VROverlay()->SetOverlayColor(overlayHandle, 1.0, 1.0, 1.0);
	VROverlay()->SetOverlayWidthInMeters(overlayHandle, 0.25f);
	VROverlay()->SetOverlayFromFile(overlayHandle, "C:/Users/ekazu/Pictures/gimp/gnome_space_4.png");
	VROverlay()->ShowOverlay(overlayHandle);

	VROverlay()->SetOverlayInputMethod(overlayHandle, vr::VROverlayInputMethod_Mouse);
	const HmdVector2_t imageSize = HmdVector2_t{ 500.0, 570.0 };
	VROverlay()->SetOverlayMouseScale(overlayHandle, &imageSize);

	HmdVector3_t pos = HmdVector3_t{0.125, 0, 0};
	HmdVector3_t rot = HmdVector3_t{-M_PI / 2.0, 0, 0};
	HmdMatrix34_t transform = MathUtils::matrix(pos, rot);

	VROverlay()->SetOverlayTransformTrackedDeviceRelative(overlayHandle, 3, &transform);

	logTrackedDevices();

	bool running = true;
	bool hasEvent = false;
	VREvent_t vrEvent;

	while (running) {
		hasEvent = VROverlay()->PollNextOverlayEvent(overlayHandle, &vrEvent, sizeof(vrEvent));

		if (!hasEvent) {
			continue;
		}

		//std::cout << "Got an event with id: " << vrEvent.eventType << std::endl;

		switch (vrEvent.eventType) {
			case VREvent_MouseMove:
				std::cout << "Mouse move event" << std::endl;
				break;

			case VREvent_MouseButtonDown:
				std::cout << "Mouse down event" << std::endl;
				break;

			case VREvent_MouseButtonUp:
				std::cout << "Mouse up event" << std::endl;
				break;

			case VREvent_OverlayShown:
				std::cout << "Overlay shown event" << std::endl;
				break;

			case VREvent_OverlayHidden:
				std::cout << "Overlay hidden event" << std::endl;
				break;

			case VREvent_Quit:
				std::cout << "VR quit event" << std::endl;
				running = false;
				break;
		}
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
