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

// 24340, 26558, 28884 - Meteor
// 26789 - Shard of the Fallen Star
struct MeteorScript : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0)
        {
            uint32 count = 0;
            for (const auto& ihit : spell->m_UniqueTargetInfo)
                if (ihit.effectMask & (1 << effIdx))
                    ++count;

            spell->damage /= count; // divide to all targets
        }
    }
};

SpellScript* GetScript_Meteor(SpellEntry const*)
{
    return new MeteorScript();
}

// 24933 - Cannon (Darkmoon Steam Tonk)
struct DarkmoonSteamTonkCannonScript : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const final
    {
        if (effIdx == EFFECT_INDEX_0 && spell->GetUnitTarget())
        {
            spell->m_caster->CastSpell(spell->GetUnitTarget(), 27766, true);
        }
    }
};

SpellScript* GetScript_DarkmoonSteamTonkCannon(SpellEntry const*)
{
    return new DarkmoonSteamTonkCannonScript();
}

void AddSC_special_spell_scripts()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "spell_meteor";
    newscript->GetSpellScript = &GetScript_Meteor;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_darkmoon_steam_tonk_cannon";
    newscript->GetSpellScript = &GetScript_DarkmoonSteamTonkCannon;
    newscript->RegisterSelf();
}
