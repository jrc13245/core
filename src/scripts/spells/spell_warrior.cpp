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

// 5246 - Intimidating Shout
struct WarriorIntimidatingShoutScript : SpellScript
{
    bool OnCheckTarget(Spell const* spell, Unit* target, SpellEffectIndex /*eff*/) const final
    {
        // Exception: Intimidating Shout
        // The AoE fear does not apply to spell main target (that is stunned by another aura)
        if (target == spell->m_targets.getUnitTarget())
            return false;
        return true;
    }
};

SpellScript* GetScript_WarriorIntimidatingShout(SpellEntry const*)
{
    return new WarriorIntimidatingShoutScript();
}

// 23881, 23892, 23893, 23894 - Bloodthirst
struct WarriorBloodthirstScript : SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0 && spell->m_casterUnit)
        {
            float attackPower = spell->m_casterUnit->GetTotalAttackPowerValue(BASE_ATTACK);
            if (spell->GetUnitTarget())
                attackPower += spell->m_casterUnit->GetTotalAuraModifierByMiscMask(SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS, spell->GetUnitTarget()->GetCreatureTypeMask());
            spell->damage = spell->damage * attackPower / 100;
        }
        return true;
    }
};

SpellScript* GetScript_WarriorBloodthirst(SpellEntry const*)
{
    return new WarriorBloodthirstScript();
}

// 23922, 23923, 23924, 23925 - Shield Slam
struct WarriorShieldSlamScript : SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_1 && spell->m_casterUnit)
        {
            spell->damage += spell->m_casterUnit->GetShieldBlockValue();
        }
        return true;
    }
};

SpellScript* GetScript_WarriorShieldSlam(SpellEntry const*)
{
    return new WarriorShieldSlamScript();
}

// 20647 - Execute
struct WarriorExecuteDamageScript : SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0 && spell->m_casterUnit)
        {
            spell->m_casterUnit->SetPower(POWER_RAGE, 0);
        }
        return true;
    }
};

SpellScript* GetScript_WarriorExecuteDamage(SpellEntry const*)
{
    return new WarriorExecuteDamageScript();
}

// 5308, 20658, 20660, 20661, 20662 - Execute
struct WarriorExecuteDummyScript : SpellScript
{
    void OnCast(Spell* spell) const final
    {
        if (!spell->GetUnitTarget() || !spell->m_casterUnit)
            return;
        
        int32 basePoints0 = spell->m_currentBasePoints[0] + dither(spell->m_casterUnit->GetPower(POWER_RAGE) * spell->m_spellInfo->DmgMultiplier[0]);
        // m_casterUnit->SetPower(POWER_RAGE, 0); // Done in spell 20647
        spell->m_casterUnit->CastCustomSpell(spell->GetUnitTarget(), 20647, basePoints0, {}, {}, true, nullptr);
    }
};

SpellScript* GetScript_WarriorExecuteDummy(SpellEntry const*)
{
    return new WarriorExecuteDummyScript();
}

// 21977 - Warrior's Wrath
struct WarriorWrathScript : SpellScript
{
    bool OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0)
        {
            if (!spell->GetUnitTarget())
                return false;

            spell->m_caster->CastSpell(spell->GetUnitTarget(), 21887, true); // spell mod
        }
        return true;
    }
};

SpellScript* GetScript_WarriorWrath(SpellEntry const*)
{
    return new WarriorWrathScript();
}

void AddSC_warrior_spell_scripts()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "spell_warrior_intimidating_shout";
    newscript->GetSpellScript = &GetScript_WarriorIntimidatingShout;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_warrior_bloodthirst";
    newscript->GetSpellScript = &GetScript_WarriorBloodthirst;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_warrior_shield_slam";
    newscript->GetSpellScript = &GetScript_WarriorShieldSlam;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_warrior_execute_damage";
    newscript->GetSpellScript = &GetScript_WarriorExecuteDamage;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_warrior_execute_dummy";
    newscript->GetSpellScript = &GetScript_WarriorExecuteDummy;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_warrior_wrath";
    newscript->GetSpellScript = &GetScript_WarriorWrath;
    newscript->RegisterSelf();
}
