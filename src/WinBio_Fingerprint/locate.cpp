#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <winbio.h>

HRESULT LocateSensor()
{
	HRESULT hr = S_OK;
	WINBIO_SESSION_HANDLE sessionHandle = NULL;
	WINBIO_UNIT_ID unitId = 0;

	// Connect to the system pool. 
	hr = WinBioOpenSession(
		WINBIO_TYPE_FINGERPRINT,    // Service provider
		WINBIO_POOL_SYSTEM,         // Pool type
		WINBIO_FLAG_DEFAULT,        // Configuration and access
		NULL,                       // Array of biometric unit IDs
		0,                          // Count of biometric unit IDs
		NULL,                       // Database ID
		&sessionHandle              // [out] Session handle
	);
	if (FAILED(hr))
	{
		wprintf_s(L"\n WinBioEnumBiometricUnits failed. hr = 0x%x\n", hr);
		goto e_Exit;
	}

	// Locate the sensor.
	wprintf_s(L"\n Tap the sensor once...\n");
	hr = WinBioLocateSensor(sessionHandle, &unitId);
	if (FAILED(hr))
	{
		wprintf_s(L"\n WinBioLocateSensor failed. hr = 0x%x\n", hr);
		goto e_Exit;
	}
	wprintf_s(L"\n Sensor located successfully. ");
	wprintf_s(L"\n Unit ID = %d \n", unitId);

e_Exit:
	if (sessionHandle != NULL)
	{
		WinBioCloseSession(sessionHandle);
		sessionHandle = NULL;
	}

	wprintf_s(L"\n Hit any key to exit...");
	_getch();

	return hr;
}