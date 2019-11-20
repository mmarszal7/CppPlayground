#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <winbio.h>

HRESULT LocateSensor();
HRESULT EnrollSysPoolWithCallback(BOOL bCancel, BOOL bDiscard, WINBIO_BIOMETRIC_SUBTYPE subFactor);
HRESULT Verify(WINBIO_BIOMETRIC_SUBTYPE subFactor);

int main()
{
	HRESULT hr = S_OK;

	//hr = LocateSensor();

	//hr = EnrollSysPoolWithCallback(
	//	FALSE,
	//	FALSE,
	//	WINBIO_ANSI_381_POS_RH_INDEX_FINGER);

	hr = Verify(WINBIO_ANSI_381_POS_RH_INDEX_FINGER);

	return 0;
}