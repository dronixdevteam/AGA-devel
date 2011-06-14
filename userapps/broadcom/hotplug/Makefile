all:
	cp hotplug_$(PROFILE)_save original_hotplug

PROGRAM_NAME:= original_hotplug

install::
	install -m 755 $(PROGRAM_NAME) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/$(PROGRAM_NAME)
	ln -sf ../var/hotplug $(INSTALL_DIR)/sbin/hotplug
#	ln -sf ../bin/$(PROGRAM_NAME) $(INSTALL_DIR)/sbin/hotplug

dynamic: all install

dynamic: all install

clean:
	rm -f original_hotplug

