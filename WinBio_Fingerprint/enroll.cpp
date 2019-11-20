#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <winbio.h>

VOID CALLBACK EnrollCaptureCallback(
	__in_opt PVOID EnrollCallbackContext,
	__in HRESULT OperationStatus,
	__in WINBIO_REJECT_DETAIL RejectDetail);

typedef struct _ENROLL_CALLBACK_CONTEXT {
	WINBIO_SESSION_HANDLE SessionHandle;
	WINBIO_UNIT_ID UnitId;
	WINBIO_BIOMETRIC_SUBTYPE SubFactor;
} ENROLL_CALLBACK_CONTEXT, * PENROLL_CALLBACK_CONTEXT;

//------------------------------------------------------------------------
// The following function enrolls a user's fingerprint in the system pool.
// The function calls WinBioEnrollCaptureWithCallback and waits for the
// asynchronous enrollment process to be completed or canceled.
//
HRESULT EnrollSysPoolWithCallback(
	BOOL bCancel,
	BOOL bDiscard,
	WINBIO_BIOMETRIC_SUBTYPE subFactor)
{
	// Declare variables
	HRESULT hr = S_OK;
	WINBIO_IDENTITY identity = { 0 };
	WINBIO_SESSION_HANDLE sessionHandle = NULL;
	WINBIO_UNIT_ID unitId = 0;
	BOOLEAN isNewTemplate = TRUE;
	ENROLL_CALLBACK_CONTEXT callbackContext = { 0 };

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
		wprintf_s(L"\n WinBioEnumBiometricUnits failed. ");
		wprintf_s(L"hr = 0x%x\n", hr);
		goto e_Exit;
	}

	// Locate the sensor.
	wprintf_s(L"\n Swipe your finger to locate the sensor...\n");
	hr = WinBioLocateSensor(sessionHandle, &unitId);
	if (FAILED(hr))
	{
		wprintf_s(L"\n WinBioLocateSensor failed. hr = 0x%x\n", hr);
		goto e_Exit;
	}

	// Begin the enrollment sequence. 
	hr = WinBioEnrollBegin(
		sessionHandle,      // Handle to open biometric session
		subFactor,          // Finger to create template for
		unitId              // Biometric unit ID
	);
	if (FAILED(hr))
	{
		wprintf_s(L"\n WinBioEnrollBegin failed. hr = 0x%x\n", hr);
		goto e_Exit;
	}

	// Set up the custom callback context structure.
	callbackContext.SessionHandle = sessionHandle;
	callbackContext.UnitId = unitId;
	callbackContext.SubFactor = subFactor;

	// Call WinBioEnrollCaptureWithCallback. This is an asynchronous
	// method that returns immediately.
	hr = WinBioEnrollCaptureWithCallback(
		sessionHandle,          // Handle to open biometric session
		EnrollCaptureCallback,  // Callback function
		&callbackContext        // Pointer to the custom context
	);
	if (FAILED(hr))
	{
		wprintf_s(L"\n WinBioEnrollCaptureWithCallback failed. ");
		wprintf_s(L"hr = 0x%x\n", hr);
		goto e_Exit;
	}
	wprintf_s(L"\n Swipe the sensor with the appropriate finger...\n");

	// Cancel the enrollment if the bCancel flag is set.
	if (bCancel)
	{
		wprintf_s(L"\n Starting CANCEL timer...\n");
		Sleep(7000);

		wprintf_s(L"\n Calling WinBioCancel\n");
		hr = WinBioCancel(sessionHandle);
		if (FAILED(hr))
		{
			wprintf_s(L"\n WinBioCancel failed. hr = 0x%x\n", hr);
			goto e_Exit;
		}
	}

	// Wait for the asynchronous enrollment process to complete
	// or be canceled.
	hr = WinBioWait(sessionHandle);
	if (FAILED(hr))
	{
		wprintf_s(L"\n WinBioWait failed. hr = 0x%x\n", hr);
	}

	// Discard the enrollment if the bDiscard flag is set.
	// Commit the enrollment if the flag is not set.
	if (bDiscard)
	{
		wprintf_s(L"\n Discarding enrollment...\n");
		hr = WinBioEnrollDiscard(sessionHandle);
		if (FAILED(hr))
		{
			wprintf_s(L"\n WinBioLocateSensor failed. ");
			wprintf_s(L"hr = 0x%x\n", hr);
		}
		goto e_Exit;
	}
	else
	{
		wprintf_s(L"\n Committing enrollment...\n");
		hr = WinBioEnrollCommit(
			sessionHandle,      // Handle to open biometric session
			&identity,          // WINBIO_IDENTITY object for the user
			&isNewTemplate);    // Is this a new template

		if (FAILED(hr))
		{
			wprintf_s(L"\n WinBioEnrollCommit failed. hr = 0x%x\n", hr);
			goto e_Exit;
		}
	}

e_Exit:
	if (sessionHandle != NULL)
	{
		WinBioCloseSession(sessionHandle);
		sessionHandle = NULL;
	}

	wprintf_s(L"\n Press any key to exit...");
	_getch();

	return hr;
}

//------------------------------------------------------------------------
// The following function is the callback for the Windows Biometric
// Framework WinBioEnrollCaptureWithCallback() function. 
//
VOID CALLBACK EnrollCaptureCallback(
	__in_opt PVOID EnrollCallbackContext,
	__in HRESULT OperationStatus,
	__in WINBIO_REJECT_DETAIL RejectDetail
)
{
	// Declare variables.
	HRESULT hr = S_OK;
	static SIZE_T swipeCount = 1;

	PENROLL_CALLBACK_CONTEXT callbackContext =
		(PENROLL_CALLBACK_CONTEXT)EnrollCallbackContext;

	wprintf_s(L"\n EnrollCaptureCallback executing\n");
	wprintf_s(L"\n Sample %d captured", swipeCount++);

	// The capture was not acceptable or the enrollment operation
	// failed.
	if (FAILED(OperationStatus))
	{
		if (OperationStatus == WINBIO_E_BAD_CAPTURE)
		{
			wprintf_s(L"\n Bad capture; reason: %d\n", RejectDetail);
			wprintf_s(L"\n Swipe your finger to capture another sample.\n");

			// Try again.
			hr = WinBioEnrollCaptureWithCallback(
				callbackContext->SessionHandle, // Open session handle
				EnrollCaptureCallback,          // Callback function
				EnrollCallbackContext           // Callback context
			);
			if (FAILED(hr))
			{
				wprintf_s(L"WinBioEnrollCaptureWithCallback failed.");
				wprintf_s(L"hr = 0x%x\n", hr);
			}
		}
		else
		{
			wprintf_s(L"EnrollCaptureCallback failed.");
			wprintf_s(L"OperationStatus = 0x%x\n", OperationStatus);
		}
		goto e_Exit;
	}

	// The enrollment operation requires more fingerprint swipes.
	// This is normal and depends on your hardware. Typically, at least
	// three swipes are required.
	if (OperationStatus == WINBIO_I_MORE_DATA)
	{
		wprintf_s(L"\n More data required.");
		wprintf_s(L"\n Swipe your finger on the sensor again.");

		hr = WinBioEnrollCaptureWithCallback(
			callbackContext->SessionHandle,
			EnrollCaptureCallback,
			EnrollCallbackContext
		);
		if (FAILED(hr))
		{
			wprintf_s(L"WinBioEnrollCaptureWithCallback failed. ");
			wprintf_s(L"hr = 0x%x\n", hr);
		}
		goto e_Exit;
	}

	wprintf_s(L"\n Template completed\n");

e_Exit:

	return;
}