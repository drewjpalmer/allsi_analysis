const double z_min_d = 25.; // cm (z of the first disk)
const double z_max_d = 121.; // cm (z of the last disk)
const double nDisks_in_barrel_region = 4.; //num disks in barrel region not including disk ant connecting region
const double nDisks_in_disk_region = nDisks_per_side-nDisks_in_barrel_region-1; //num disks in disk region not including disk ant connecting region
const double z_connect_d = 66.8; //cm (z of connection between flat barrel and sloping support)
const double disk_to_disk_distance_barr = (z_connect_d-z_min_d)/((float)nDisks_in_barrel_region);
const double disk_to_disk_distance_disk = (z_max_d-z_connect_d)/((float)nDisks_in_disk_region);
const int nDisks = nDisks_per_side*2;

for(int i = 0 ; i < nDisks_in_disk_region   ; i++) si_z_pos[i] = -z_max_d + (float)i*disk_to_disk_distance_disk;
for(int i =0; i<nDisks_in_barrel_region+1; i++) si_z_pos[i+nDisks_in_disk_region] = -z_connect_d + (float)(i)*disk_to_disk_distance_barrel;

for(int i = 0 ; i < nDisks_in_disk_region   ; i++) si_z_pos[i] = -z_max_d + (float)i*disk_to_disk_distance_disk;
for(int i =0; i<nDisks_in_barrel_region+1; i++) si_z_pos[i+nDisks_in_disk_region] = -z_connect_d + (float)(i)*disk_to_disk_distance_barrel;






double si_z_pos[nDisks] = {0};
double si_r_max[nDisks] = {0};
double si_r_min[nDisks] = {0};
double si_thick_disk = disk_matBud/100.*9.37;
	

for(int i = 0 ; i < nDisks ; i++){
	si_r_max[i] = TMath::Min(43.23,18.5*abs(si_z_pos[i])/si_z_pos[0]);

	if(si_z_pos[i]>66.8&&si_z_pos[i]>0) si_r_min[i] = (0.05025461*si_z_pos[i]-0.180808);
	else if(si_z_pos[i]>0) si_r_min[i] = 3.18;
	else if(si_z_pos[i]<-79.8&&si_z_pos[i]<0) si_r_min[i] = (-0.0297039*si_z_pos[i]+0.8058281);
	else si_r_min[i] = 3.18;

	si_r_max[i] -= si_r_min[i];

	cout << "Rmin, Rmax: " << si_r_min[i] << " " << si_r_max[i] << endl;