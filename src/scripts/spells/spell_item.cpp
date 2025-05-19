/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "scriptPCH.h"

// 2833 - Heavy Armor Kit
struct HeavyArmorKitScript : public SpellScript
{
    SpellCastResult OnCheckCast(Spell* spell, bool strict) const final
    {
        Item* targetItem = spell->m_targets.getItemTarget();
        if (targetItem->GetProto()->ItemLevel < 15)
            return SPELL_FAILED_LOWLEVEL;
        return SPELL_CAST_OK;
    }
};

SpellScript* GetScript_HeavyArmorKit(SpellEntry const*)
{
    return new HeavyArmorKitScript();
}

// 8063 - Deviate Fish
struct DeviateFishScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0)
        {
            Player* pPlayer = spell->GetCaster()->ToPlayer();
            if (!pPlayer)
                return false;

            uint32 randomSpellId = PickRandomValue(
                8064u, // Sleepy
                8065u, // Invigorate
                8066u, // Shrink
                8067u, // Party Time!
                8068u, // Healthy Spirit
                8070u  // Rejuvenation
            );

            pPlayer->CastSpell(pPlayer, randomSpellId, true, nullptr);
        }
        return true;
    }
};

SpellScript* GetScript_DeviateFish(SpellEntry const*)
{
    return new DeviateFishScript();
}

// 8213 - Cooked Deviate Fish
struct CookedDeviateFishScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0)
        {
            Player* pPlayer = spell->GetCaster()->ToPlayer();
            if (!pPlayer)
                return false;

            uint32 randomSpellId = 0;
            uint32 spells[6] = {
                (pPlayer->GetGender() == GENDER_MALE ? 8219u : 8220u), // Flip Out - ninja
                (pPlayer->GetGender() == GENDER_MALE ? 8221u : 8222u), // Yaaarrrr - pirate
                8223u, // Oops - goo
                8215u, // Rapid Cast
                8224u, // Cowardice
                8226u  // Fake Death
            };

            // Had additional effects before BWL patch.
#if SUPPORTED_CLIENT_BUILD <= CLIENT_BUILD_1_5_1
            randomSpellId = spells[urand(0, 5)];
#else
            randomSpellId = spells[urand(0, 1)];
#endif
            pPlayer->CastSpell(pPlayer, randomSpellId, true, nullptr);
        }
        return true;
    }
};

SpellScript* GetScript_CookedDeviateFish(SpellEntry const*)
{
    return new CookedDeviateFishScript();
}

// 16589 - Noggenfogger Elixir
struct NoggenfoggerElixirScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0)
        {
            Player* pPlayer = spell->GetCaster()->ToPlayer();
            if (!pPlayer)
                return false;

            // https://old.reddit.com/r/classicwow/comments/jwycmc/noggenfogger_1000_consumes_593_skellies_210_minis/
            uint32 randomSpellId = 16591; // skeleton (60%)
            switch (urand(1, 10))
            {
                case 1:
                case 2:
                {
                    randomSpellId = 16595; // mini (20%)
                    break;
                }
                case 3:
                case 4:
                {
                    randomSpellId = 16593; // slow fall (20%)
                    break;
                }
            }

            pPlayer->CastSpell(pPlayer, randomSpellId, true, nullptr);
        }
        return true;
    }
};

SpellScript* GetScript_NoggenfoggerElixir(SpellEntry const*)
{
    return new NoggenfoggerElixirScript();
}

// 15712 - Linken's Boomerang
struct LinkensBoomerangScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        // 10% chance to proc stun, 3% chance to proc disarm (dubious numbers)
        if (effIdx == EFFECT_INDEX_1)
        {
            if (urand(0, 30))
                return false;
        }
        else if (effIdx == EFFECT_INDEX_2)
        {
            if (urand(0, 10))
                return false;
        }
        return true;
    }
};

SpellScript* GetScript_LinkensBoomerang(SpellEntry const*)
{
    return new LinkensBoomerangScript();
}

// 6410 - Food (Scorpid Surprise)
struct ScorpidSurpriseScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_1)
        {
            // Heals 294 damage over 21 sec, assuming you don't bite down on a poison sac.
            // 10% proc rate (no source !)
            if (urand(0, 10))
                return false;
        }
        return true;
    }
};

SpellScript* GetScript_ScorpidSurprise(SpellEntry const*)
{
    return new ScorpidSurpriseScript();
}

// 29284 - Brittle Armor (Zandalarian Hero Badge)
struct BrittleArmorDummyScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0 && spell->GetUnitTarget())
        {
            spell->m_caster->CastSpell(spell->GetUnitTarget(), 24575, true);
        }
        return true;
    }
};

SpellScript* GetScript_BrittleArmorDummy(SpellEntry const*)
{
    return new BrittleArmorDummyScript();
}

// 29286 - Mercurial Shield (Petrified Scarab)
struct MercurialShieldDummyScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0 && spell->GetUnitTarget())
        {
            spell->m_caster->CastSpell(spell->GetUnitTarget(), 26464, true);
        }
        return true;
    }
};

SpellScript* GetScript_MercurialShieldDummy(SpellEntry const*)
{
    return new MercurialShieldDummyScript();
}

// 23442 - Everlook Transporter (Dimensional Ripper - Everlook)
struct EverlookTransporterScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0 && spell->m_casterUnit)
        {
            int32 r = irand(0, 119);
            if (r >= 70)                                    // 7/12 success
            {
                if (r < 100)                                // 4/12 evil twin
                    spell->m_casterUnit->CastSpell(spell->m_casterUnit, 23445, true);
                else                                        // 1/12 fire
                    spell->m_casterUnit->CastSpell(spell->m_casterUnit, 23449, true);
            }
        }
        return true;
    }
};

SpellScript* GetScript_EverlookTransporter(SpellEntry const*)
{
    return new EverlookTransporterScript();
}

enum
{
    SPELL_GDR_CHANNEL = 13278,
    SPELL_GDR_PERIODIC_DAMAGE = 13493,
    SPELL_GDR_DAMAGE_HIT = 13279,
};

struct GDRChannelScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_1)
            spell->GetCaster()->CastSpell(nullptr, SPELL_GDR_PERIODIC_DAMAGE, true);
        return true;
    }
};

SpellScript* GetScript_GDRChannel(SpellEntry const*)
{
    return new GDRChannelScript();
}

struct GDRPeriodicDamageScript : public AuraScript
{
    int32 dmg = 0;

    int32 OnAuraValueCalculate(Aura* /*aura*/, Unit* /*caster*/, Unit* /*target*/, SpellEntry const* /*spellProto*/, SpellEffectIndex /*effIdx*/, Item* /*castItem*/, int32 /*value*/) final
    {
        return urand(100, 500);
    }

    void OnPeriodicCalculateAmount(Aura* aura, float& amount) final
    {
        Spell* channel = aura->GetTarget()->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
        if (!channel || channel->m_spellInfo->Id != SPELL_GDR_CHANNEL)
            amount = 0;

        dmg += amount;
    }

    void OnAfterApply(Aura* aura, bool apply) final
    {
        if (!apply && aura->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE && dmg)
        {
            if (ObjectGuid targetGuid = aura->GetTarget()->GetTargetGuid())
                if (Unit* pTarget = aura->GetTarget()->GetMap()->GetUnit(targetGuid))
                    aura->GetTarget()->CastCustomSpell(pTarget, SPELL_GDR_DAMAGE_HIT, dmg, {}, {}, true);
        }
    }
};

AuraScript* GetScript_GDRPeriodicDamage(SpellEntry const*)
{
    return new GDRPeriodicDamageScript();
}

// 4071 - Target Dummy
// 4072 - Advanced Target Dummy
// 19805 - Masterwork Target Dummy
struct TargetDummyScript : SpellScript
{
    void OnSummon(Spell* spell, Creature* summon) const final
    {
        summon->SetFactionTemporary(spell->m_caster->GetFactionTemplateId(), TEMPFACTION_NONE);
        summon->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
    }
};

SpellScript* GetScript_TargetDummy(SpellEntry const*)
{
    return new TargetDummyScript();
}

// 12766 - Poison Cloud (Chained Essence of Eranikus)
struct ChainedEssenceOfEranikusScript : SpellScript
{
    void OnSummon(Spell* spell, Creature* summon) const final
    {
        if (spell->m_casterUnit)
        {
            uint32 textId = PickRandomValue(4438, 4439, 4440, 4441, 4442, 4443, 4444, 4445);
            summon->MonsterWhisper(textId, spell->m_casterUnit);
        }
    }
};

SpellScript* GetScript_ChainedEssenceOfEranikus(SpellEntry const*)
{
    return new ChainedEssenceOfEranikusScript();
}

// 17166 - Release Umi's Yeti
struct ReleaseUmisYetiScript : SpellScript
{
    void OnSummon(Spell* spell, Creature* summon) const final
    {
        // Release Umi's Yeti - Quest Are We There, Yeti? Part 3
        summon->MonsterTextEmote(6327);
        summon->MonsterSay(9055);

        switch (summon->GetAreaId())
        {
            case 541: // Un'Goro Crater
                if (Creature* pCreature = summon->FindNearestCreature(10977, 30.0f, true)) // NPC_QUIXXIL
                {
                    summon->GetMotionMaster()->MoveFollow(pCreature, 0.6f, M_PI_F);
                    pCreature->MonsterSay(6314);
                    pCreature->SetWalk(false);
                    pCreature->GetMotionMaster()->MoveWaypoint(0, 0, 0, 0, 0, false);
                }
                break;
            case 976: // Tanaris
                if (Creature* pCreature = summon->FindNearestCreature(7583, 30.0f, true)) // NPC_SPRINKLE
                {
                    summon->GetMotionMaster()->MoveFollow(pCreature, 0.6f, M_PI_F);
                    pCreature->MonsterTextEmote(6301);
                    pCreature->SetWalk(false);
                    pCreature->GetMotionMaster()->MoveWaypoint(0, 0, 0, 0, 0, false);
                }
                break;
            case 2255: // Winterspring
                if (Creature* pCreature = summon->FindNearestCreature(10978, 30.0f, true)) // NPC_LEGACKI
                {
                    summon->GetMotionMaster()->MoveFollow(pCreature, 0.6f, M_PI_F);
                    pCreature->MonsterTextEmote(6306);
                    pCreature->SetWalk(false);
                    pCreature->GetMotionMaster()->MoveWaypoint(0, 0, 0, 0, 0, false);
                }
                break;
        }
    }
};

SpellScript* GetScript_ReleaseUmisYeti(SpellEntry const*)
{
    return new ReleaseUmisYetiScript();
}

// 26391 - Tentacle Call (Vanquished Tentacle of C'Thun)
struct VanquishedTentacleofCthunScript : SpellScript
{
    void OnSummon(Spell* spell, Creature* summon) const final
    {
        CharmInfo *charmInfo = summon->GetCharmInfo();
        charmInfo->SetIsAtStay(true);
        charmInfo->SetCommandState(COMMAND_STAY);
        charmInfo->SetIsCommandFollow(false);
        charmInfo->SaveStayPosition();
    }
};

SpellScript* GetScript_VanquishedTentacleofCthun(SpellEntry const*)
{
    return new VanquishedTentacleofCthunScript();
}

// 8342 - Defibrillate (Goblin Jumper Cables)
struct GoblinJumperCablesScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0 && spell->m_casterUnit)
        {
            // Defibrillate (Goblin Jumper Cables) have 33% chance on success
            if (roll_chance_i(67))
            {
                if (spell->m_casterUnit)
                    spell->m_casterUnit->CastSpell(spell->m_casterUnit, 8338, true, spell->m_CastItem);
                return false;
            }
        }
        return true;
    }
};

SpellScript* GetScript_GoblinJumperCables(SpellEntry const*)
{
    return new GoblinJumperCablesScript();
}

// 22999 - Defibrillate (Goblin Jumper Cables XL)
struct GoblinJumperCablesXLScript : public SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0 && spell->m_casterUnit)
        {
            // Defibrillate (Goblin Jumper Cables XL) have 50% chance on success
            if (roll_chance_i(50))
            {
                if (spell->m_casterUnit)
                    spell->m_casterUnit->CastSpell(spell->m_casterUnit, 23055, true, spell->m_CastItem);
                return false;
            }
        }
        return true;
    }
};

SpellScript* GetScript_GoblinJumperCablesXL(SpellEntry const*)
{
    return new GoblinJumperCablesXLScript();
}

// 25860 - Reindeer Transformation (Fresh Holly, Preserved Holly)
struct ReindeerTransformationScript : SpellScript
{
    SpellCastResult OnCheckCast(Spell* spell, bool /*strict*/) const final
    {
        if (!spell->m_casterUnit || !spell->m_casterUnit->HasAuraType(SPELL_AURA_MOUNTED))
            return SPELL_FAILED_ONLY_MOUNTED;
        return SPELL_CAST_OK;
    }
};

SpellScript* GetScript_ReindeerTransformation(SpellEntry const*)
{
    return new ReindeerTransformationScript();
}

// 25720 - Place Loot (Bag of Gold), Quest 8606 Decoy!
struct BagOfGoldScript : SpellScript
{
    SpellCastResult OnCheckCast(Spell* spell, bool /*strict*/) const final
    {
        if (Player* pPlayer = ToPlayer(spell->GetAffectiveCaster()))
            if (!pPlayer->HasAura(25688)) // Narain's Turban
                return SPELL_FAILED_TARGET_AURASTATE;
        return SPELL_CAST_OK;
    }
};

SpellScript* GetScript_BagOfGold(SpellEntry const*)
{
    return new BagOfGoldScript();
}

// 4067 - Big Bronze Bomb
// 13237 - Goblin Mortar
struct InstantCastScript : SpellScript
{
    void OnSuccessfulStart(Spell* spell) const final
    {
        spell->SetCastTime(0);
        spell->ReSetTimer();
    }
};

SpellScript* GetScript_InstantCast(SpellEntry const*)
{
    return new InstantCastScript();
}

void AddSC_item_spell_scripts()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "spell_heavy_armor_kit";
    newscript->GetSpellScript = &GetScript_HeavyArmorKit;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_deviate_fish";
    newscript->GetSpellScript = &GetScript_DeviateFish;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_cooked_deviate_fish";
    newscript->GetSpellScript = &GetScript_CookedDeviateFish;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_noggenfogger_elixir";
    newscript->GetSpellScript = &GetScript_NoggenfoggerElixir;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_linkens_boomerang";
    newscript->GetSpellScript = &GetScript_LinkensBoomerang;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_scorpid_surprise";
    newscript->GetSpellScript = &GetScript_ScorpidSurprise;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_brittle_armor_dummy";
    newscript->GetSpellScript = &GetScript_BrittleArmorDummy;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_mercurial_shield_dummy";
    newscript->GetSpellScript = &GetScript_MercurialShieldDummy;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_everlook_transporter";
    newscript->GetSpellScript = &GetScript_EverlookTransporter;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_gdr_channel";
    newscript->GetSpellScript = &GetScript_GDRChannel;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_gdr_periodic";
    newscript->GetAuraScript = &GetScript_GDRPeriodicDamage;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_target_dummy";
    newscript->GetSpellScript = &GetScript_TargetDummy;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_chained_essence_of_eranikus";
    newscript->GetSpellScript = &GetScript_ChainedEssenceOfEranikus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_release_umis_yeti";
    newscript->GetSpellScript = &GetScript_ReleaseUmisYeti;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_vanquished_tentacle_of_cthun";
    newscript->GetSpellScript = &GetScript_VanquishedTentacleofCthun;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_goblin_jumper_cables";
    newscript->GetSpellScript = &GetScript_GoblinJumperCables;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_goblin_jumper_cables_xl";
    newscript->GetSpellScript = &GetScript_GoblinJumperCablesXL;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_reindeer_transformation";
    newscript->GetSpellScript = &GetScript_ReindeerTransformation;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_bag_of_gold";
    newscript->GetSpellScript = &GetScript_BagOfGold;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_instant_cast";
    newscript->GetSpellScript = &GetScript_InstantCast;
    newscript->RegisterSelf();
}
