# okumaMtconnect

The ``.xml`` files are the files we download from the page okuma is publishing. 

The okuma is net configured to speak with the Raspberry Pi: No DHCP and static IP Address, from both sides.

To download okuma's file

``curl -i http://192.168.1.2:5000/current``

the file is processed by mtconnectApi and let a
``mtconnect-YYYY-MM-DD-HH-MM-SS.json`` file
that is upload directly to the API.

	- machineId = fixed - net card exa number
	- startTime = time of pexecution
	- status = value of pexecution

``
'{
    "machineId": "3f7b0d7a-097f-4188-bd03-48b06a8e6eb0",
    "startTime": "2024-10-21T09:00:00.740Z",
    "status": "RUNNING"
}'
``

Okuma examples were downloaded from this web,provided by okuma
``https://smstestbed.nist.gov/vds/``

