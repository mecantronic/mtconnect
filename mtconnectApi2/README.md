# Steps to make it work

1. install `cifs-utils`
2. make an `.sh` file
	a. `sudo` command without password prompting
3. in `/etc/sudoers` file
	a. sudo	ALL=(ALL) NOPASSWD: ALL
	b. root ALL=(ALL) NOPASSWD: ALL
	c. user ALL=(ALL) NOPASSWD: /path/to/script/script.sh
4. make service run
	a. make a unit service file in `lib/systemd/system/`
	b. content:
		[Unit]
		Description=mounting windows Service
		After=network.target

		[Service]
		Type=idle
		ExecStart=/usr/bin/bash /path/to/script.sh
		Restart=on-failure

		[Install]
		WantedBy=multi-user.target
	
	c. Make the service run on background
		`sudo systemctl enable your_service_name.service`
		`sudo systemctl start your_service_name.service`

Above is just for the mount of the windows folder on debian mnt folder.

For the read process
1. compile `parse.c`
2. make a `.sh` file to read every second
	a.	
		```
		while true
		do
			/home/okuma/mtconnect/script_or_program
			sleep 1
		done
		```
3. give the file attrib 777 (chmod)
4. make a service file (IDEM 4. before) pointing this file
5. run the service


# WORST PROBLEM

### Windows Share Folder Configuration

Can not fidn the correct config to share `c:\MD1`. It always let me share `c:\usr\fchaves\shared_folder\MD1`.
Windows 11 enterprise

## Next Steps

1. Make the output to a file, like the previous version of mtconnectApi, as `mtconnect-2024-11-10-22-12-34.json` to be send directly with the `transmition` program.
2. This would make the files to remain on the disk.
3. But is an option to let go. `fsystem` has not to be improved.
4. `tail` algorythm without `fsystem` is what to look for.
5. improve speed with `systemd interrupt service routine`
