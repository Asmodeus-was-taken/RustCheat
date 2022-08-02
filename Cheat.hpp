namespace esp {
	uintptr_t client_entities;
	base_player* local_player;
	VMatrix matrix;

	struct bounds_t {
		float left, right, top, bottom;
	};

	struct rust_str
	{
		char zpad[ 128 ];
	};

	bool out_w2s(const vector3& position, vector2& screen_pos) {
		if (!matrix.m) {
			return false;
		}

		vector2 out;
		const auto temp = matrix.transpose( );

		auto translation_vector = vector3{temp[ 3 ][ 0 ], temp[ 3 ][ 1 ], temp[ 3 ][ 2 ]};
		auto up = vector3{temp[ 1 ][ 0 ], temp[ 1 ][ 1 ], temp[ 1 ][ 2 ]};
		auto right = vector3{temp[ 0 ][ 0 ], temp[ 0 ][ 1 ], temp[ 0 ][ 2 ]};

		float w = translation_vector.dot(position) + temp[ 3 ][ 3 ];

		if (w < 0.098f) {
			return false;
		}

		float x = up.dot(position) + temp._24;
		float y = right.dot(position) + temp._14;

		out.x = (static_cast<float>(unity::get_width( )) / 2) * (1 + y / w);
		out.y = (static_cast<float>(unity::get_height( )) / 2) * (1 - x / w);

		screen_pos = out;

		return true;
	}


//all ways day 
safe_write(TodCycle + 0x10, floats::Time, float);


UINT_PTR GetName() { // player name
		auto player_name = safe_read((uintptr_t)this + oPlayerName, UINT_PTR);
		return player_name;
	}

	UINT64 SteamID() // players stream id 
	{
		return safe_read((const uintptr_t)(const uintptr_t)this + oSteamID, UINT64);
	}

	float Health() // players health
	{
		return safe_read((const uintptr_t)(const uintptr_t)this + oPlayerHealth, float);
	}

	bool Flags(int Flg) // admin or not 
	{
		return safe_read((const uintptr_t)(const uintptr_t)this + oPlayerFlags, int) & Flg;
	}

	bool Dead() // if player is dead
	{ 
		if (!(const uintptr_t)this) return true;
		return safe_read((const uintptr_t)(const uintptr_t)this + oLifestate, bool);
	}



	void Admin() // admin commands
	{
		int Flags = safe_read((const uintptr_t)this + oPlayerFlags, int);
		safe_write((const uintptr_t)this + oPlayerFlags, (Flags |= 4), int);
	}

void UnJump() // unlimited jump
	{
		auto PlayerWalkMovement = safe_read((const uintptr_t)this + oPlayerMovement, uintptr_t);
		safe_write(PlayerWalkMovement + 0xD0, 0, float); 
		safe_write(PlayerWalkMovement + 0xD4, 0, float); 
		safe_write(PlayerWalkMovement + 0xCC, 10000, float); 
	}

void Fov() // change fov
	{
		auto Class = safe_read(game_assembly + oConVar, DWORD64);
		auto Field = safe_read(Class + 0xB8, DWORD64);
		safe_write(Field + 0x18, Value::floats::Player::CustomFov, float);
	}

void Neck() { //long neck

		DWORD64 eyes = safe_read((const uintptr_t)this + oPlayerEyes, DWORD64);
		safe_write(eyes + 0x38, Vector3(0, (1.6f), 0), Vector3);
	}

void Cam() // fix cam
	{
		auto klass = safe_read(game_assembly + oConClient, DWORD64);
		auto camera = safe_read(klass + 0xB8, DWORD64);
		safe_write(camera + 0x2C, 1.f, float);
		safe_write(camera + 0x20, 1.f, float);
		safe_write(camera + 0x34, 1.f, float);
	}

oid todsky() { // always day
		UINT64 klass = safe_read(game_assembly + oTOD_Sky, UINT64);
		UINT64 static_fields = safe_read(klass + 0xB8, UINT64);
		UINT64 instances = safe_read(static_fields, UINT64);
		UINT64 List = safe_read(instances + 0x10, UINT64);
		UINT64 TOD_Sky = safe_read(List + 0x20, UINT64);
		UINT64 night = safe_read(TOD_Sky + 0x58, UINT64);
		UINT64 ambient = safe_read(TOD_Sky + 0x90, UINT64);
		safe_write(night + 0x50, 6.f, float);
		safe_write(ambient + 0x18, 4.f, float);
	}

void SpiderMan() // spider man
	{
		UINT64 Movement = safe_read((const uintptr_t)this + oPlayerMovement, UINT64);
		safe_write(Movement + oGroundAngleNew, 0.f, float);
	}
