#include "diagnostics.h"

diagnostics::diagnostics(QObject* parent) : QObject(parent) {}

QString diagnostics::check_filesystem() {
	// Making sure essential folders exist, if not, creating them
	if(!QDir("core").exists()) {
		if(!QDir().mkdir("core")) { return "Folder Permission issues?"; }
	}
	// Checking game version file exists
	if(!QFile("game.version").exists()) {
		QFile file("game.version");
		if(file.open(QIODevice::WriteOnly)) { file.write("0"); } else { return "File Permission issues?"; };
	}
	// Removing old launcher if exists
	if(QFile("woa_old.exe").exists()) {
		QFile::remove("woa_old.exe");
	}
	// Checking if game file exists
	if(!QFile("core/game.exe").exists()) { return "Unable to find game executable."; }
	qDebug() << check_digest();
	return "";
}

QString diagnostics::check_digest() {
	// Time to check launcher digest
	auto check = [](QString fn) {
		QString d;
		QFile f;
		if(fn == "woa.exe") {
			f.setFileName(QCoreApplication::applicationFilePath());
		} else {
			f.setFileName(fn);
		}

		if(f.open(QFile::ReadOnly)) {
			QCryptographicHash hash(QCryptographicHash::Sha3_512);
			if(!hash.addData(&f)) {
				return QString("");
			}
			d = QString(hash.result().toHex());
		} else {
			return QString("");
		}
		if(f.isOpen()) {
			f.close();
		}
		//qDebug() << filename << " : " << digest << "\n";
		return d;
	};

	// List of all 
	QList<QString> files_to_check;
	files_to_check << "woa.exe" << "core/game.exe" << "core/ressystem/AbState.shn" << "core/ressystem/AbStateView.shn" << "core/ressystem/AccUpgrade.shn"
		<< "core/ressystem/ActionEffectInfo.shn" << "core/ressystem/ActionViewInfo.shn" << "core/ressystem/ActiveSkill.shn"
		<< "core/ressystem/ActiveSkillGroup.shn" << "core/ressystem/ActiveSkillInfoServer.shn" << "core/ressystem/ActiveSkillView.shn"
		<< "core/ressystem/BadNameFilter.shn" << "core/ressystem/CharacterTitleData.shn" << "core/ressystem/ChargedEffect.shn"
		<< "core/ressystem/ClassName.shn" << "core/ressystem/ColorInfo.shn" << "core/ressystem/DamageEffect.shn"
		<< "core/ressystem/DamageSoundInfo.shn" << "core/ressystem/DiceDividind.shn" << "core/ressystem/DiceGame.shn"
		<< "core/ressystem/DiceRate.shn" << "core/ressystem/EffectViewInfo.shn" << "core/ressystem/EmotionFilter.shn"
		<< "core/ressystem/ErrorCodeTable.shn" << "core/ressystem/FaceInfo.shn" << "core/ressystem/Gather.shn"
		<< "core/ressystem/GradeItemOption.shn" << "core/ressystem/GTIView.shn" << "core/ressystem/GuildGradeData.shn"
		<< "core/ressystem/GuildTournamentRequire.shn" << "core/ressystem/GuildTournamentSkill.shn"
		<< "core/ressystem/GuildTournamentSkillDesc.shn" << "core/ressystem/HairColorInfo.shn"
		<< "core/ressystem/HairInfo.shn" << "core/ressystem/HolyPromiseReward.shn" << "core/ressystem/ItemDismantle.shn"
		<< "core/ressystem/ItemInfo.shn" << "core/ressystem/ItemShop.shn" << "core/ressystem/ItemShopView.shn"
		<< "core/ressystem/ItemUseEffect.shn" << "core/ressystem/ItemViewInfo.shn" << "core/ressystem/KingdomQuest.shn"
		<< "core/ressystem/KingdomQuestDesc.shn" << "core/ressystem/KingdomQuestMap.shn" << "core/ressystem/KingdomQuestRew.shn"
		<< "core/ressystem/MapInfo.shn" << "core/ressystem/MapViewInfo.shn" << "core/ressystem/MHEmotion.shn"
		<< "core/ressystem/MiniHouse.shn" << "core/ressystem/MiniHouseDummy.shn" << "core/ressystem/MiniHouseEndure.shn"
		<< "core/ressystem/MiniHouseFurniture.shn" << "core/ressystem/MiniHouseFurnitureObjEffect.shn"
		<< "core/ressystem/MiniHouseObjAni.shn" << "core/ressystem/MobCoordinate.shn" << "core/ressystem/MobInfo.shn"
		<< "core/ressystem/MobKillAnnounce.shn" << "core/ressystem/MobKillAnnounceText.shn" << "core/ressystem/MobKillLog.shn"
		<< "core/ressystem/MobSpecies.shn" << "core/ressystem/MobViewInfo.shn" << "core/ressystem/MobWeapon.shn"
		<< "core/ressystem/NpcDialogData.shn" << "core/ressystem/NPCViewInfo.shn" << "core/ressystem/PassiveSkill.shn"
		<< "core/ressystem/PassiveSkillView.shn" << "core/ressystem/Produce.shn" << "core/ressystem/ProduceView.shn"
		<< "core/ressystem/QuestData.shn" << "core/ressystem/QuestDialog.shn" << "core/ressystem/QuestScript.shn"
		<< "core/ressystem/QuestSpecies.shn" << "core/ressystem/RaceNameInfo.shn" << "core/ressystem/Riding.shn"
		<< "core/ressystem/SetItem.shn" << "core/ressystem/SetItemEffect.shn" << "core/ressystem/SetItemView.shn"
		<< "core/ressystem/ShineReward.shn" << "core/ressystem/SlanderFilter.shn" << "core/ressystem/SpamerPenalty.shn"
		<< "core/ressystem/StateMob.shn" << "core/ressystem/SubAbState.shn" << "core/ressystem/TextData.shn"
		<< "core/ressystem/TextData2.shn" << "core/ressystem/TownPortal.shn" << "core/ressystem/UpEffect.shn"
		<< "core/ressystem/UpgradeInfo.shn" << "core/ressystem/WeaponAttrib.shn" << "core/ressystem/WeaponTitleData.shn"
		<< "core/ressystem/WorldMapAvatarInfo.shn";

	QString data_digest;
	for(auto object : files_to_check) {
		auto obj_digest = check(object);
		if(obj_digest == "") {
			return "Digest check failed, please contact support.";
		}
		data_digest.append(obj_digest);
	}

	auto digest = QString(QCryptographicHash::hash(QByteArray::fromHex(data_digest.toLatin1()), QCryptographicHash::Sha3_512).toHex());
	//qDebug() << digest.right(20);
	return digest.right(20);
}
