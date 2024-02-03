class PowerUser /* ToDo: which extends? */{}

class EmergencyLight extends PowerUser {}

class PersonalComputer extends PowerUser {}

class TV extends PowerUser {}

class Asset{
	// ToDo: Implement me
}

class BuildingManager {
	Asset things[] = new Asset[24];
	int numItems = 0;

	public void powerDownAtNight() {
		for (int i = 0; i < things.length; i++)
			if (things[i]!=null)
				things[i].powerDown();
	}

	/** Add an Asset to this building */
	public void add(Asset thing) {
		things[numItems] = thing;
	}
}

public class Lab3_Q2 {
	public static void q2() {
		BuildingManager b1 = new BuildingManager();

		b1.add(new EmergencyLight());
		b1.add(new PersonalComputer());
		b1.add(new TV());
		b1.powerDownAtNight();
	}
}