#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
	int opt;
	
	printf("Benvenuto in Utility!\n");
	printf("Quale programma vuoi usare?\n");
	
	while(1) {
		printf("1. Gestione Computer\n");
		printf("2. Gestione Certificati\n");
		printf("3. Gestione Dispositivi\n");
		printf("4. Gestione Disco\n");
		printf("5. Visualizzatore eventi\n");
		printf("6. Gestione Hyper-V\n");
		printf("7. Utenti e gruppi locali\n");
		printf("8. Performance Monitor\n");
		printf("9. Gestione di Stampa\n");
		printf("10. Servizi\n");
		printf("11. Utilità di Pianificazione\n");
	    printf("12. Gestione Trusted Platform Module\n");
		printf("13. Windows Firewall con sicurezza avanzata\n");
	    printf("14. Registro Windows\n");
		printf("15. System Information\n");
	    printf("16. Prompt dei Comandi\n");
		printf("17. Check connessione\n");
		printf("18. systeminfo.exe\n");
		printf("19. Ip locale e configurazione di rete\n");
		printf("20. Exit\n");
     
		scanf("%d", &opt);
		getchar();
		opt--;

		if (opt == 19)
			exit(0);

		if (opt < 16)
			system(win_commands[opt]);
		else
			get_output(win_commands[opt], fp);
	}

#else
	get_output("lsblk", fp);
	get_output("sudo fdisk -l", fp);
	get_output("lspci -nk", fp);
	get_output("sudo dmesg --level=err", fp);
	get_output("sudo dmesg --level=warn", fp);
	system("sudo dmesg > full_dmesg.txt");
	get_output("systemctl --type=service", fp);
	get_output("cat /proc/cpuinfo", fp);
#endif 
