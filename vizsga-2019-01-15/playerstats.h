#pragma once

class PlayerStats {
public:
	Csapat * team;
	int goals;
	PlayerStats * previousStats;
	PlayerStats() : team(nullptr), goals(0), previousStats(nullptr) {}
	void goal() {
		goals += 1;
	}
	void setTeam(Csapat* c) {
		if (!team) {
			team = c;
		}
	}
	void setPrevious(PlayerStats* ps) {
		if (!previousStats) {
			previousStats = ps;
		}
	}
	
};