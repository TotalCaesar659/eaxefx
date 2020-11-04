/*

EAX OpenAL Extension

Copyright (c) 2020 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE.

*/


#ifndef EAXEFX_EAXX_SOURCE_INCLUDED
#define EAXEFX_EAXX_SOURCE_INCLUDED


#include <array>

#include "AL/al.h"

#include "eaxefx_al_low_pass_param.h"
#include "eaxefx_eaxx_eax_call.h"
#include "eaxefx_eaxx_fx_slots.h"


namespace eaxefx
{


// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

struct EaxxSourceInitParam
{
	ALuint al_source{};
	ALuint al_filter{};
	EaxxFxSlots* fx_slots{};
}; // EaxxSourceInitParam

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

class EaxxSource
{
public:
	EaxxSource(
		const EaxxSourceInitParam& param);


	void set(
		const EaxxEaxCall& eax_call);


	void update_filters();

	void on_set_primary_fx_slot_id();


private:
	using ActiveFxSlots = std::array<bool, EAX_MAX_FXSLOTS>;


	struct Al
	{
		ALuint source{};
		ALuint filter{};
	}; // Al

	struct Eax
	{
		EAX50SOURCEPROPERTIES source{};
		EAX50ACTIVEFXSLOTS active_fx_slots{};
	}; // Eax


	bool is_initialized_{};
	bool uses_primary_id_{};
	bool has_active_fx_slots_{};
	Al al_{};
	Eax eax_{};
	EaxxFxSlots* fx_slots_{};
	ActiveFxSlots active_fx_slots_{};


	static void validate_init_param(
		const EaxxSourceInitParam& param);

	void copy_init_param(
		const EaxxSourceInitParam& param);


	void set_eax_source_defaults();

	void set_eax_active_fx_slots_defaults();

	void set_eax_defaults();


	static float calculate_dst_occlusion_mb(
		long src_occlusion_mb,
		float path_ratio,
		float lf_ratio) noexcept;

	AlLowPassParam make_direct_filter() const noexcept;

	AlLowPassParam make_room_filter(
		const EaxxFxSlot& fx_slot) const noexcept;

	void set_al_filter_parameters(
		const AlLowPassParam& al_low_pass_param) const noexcept;

	void initialize_fx_slots();

	void initialize(
		const EaxxSourceInitParam& param);


	void update_direct_filter_internal();

	void update_room_filters_internal();

	void update_filters_internal();


	void set_direct_hf_auto_flag();

	void set_room_auto_flag();

	void set_room_hf_auto_flag();

	void set_flags();


	void set_obstruction_all(
		const EAXOBSTRUCTIONPROPERTIES& eax_obstruction_properties);

	void set_occlusion_all(
		const EAXOCCLUSIONPROPERTIES& eax_occlusion_properties);

	void set_room(
		long eax_room);

	void set_occlusion(
		long eax_occlusion);

	void set_exclusion(
		long eax_exclusion);

	void set_flags(
		unsigned long eax_flags);

	void set_active_fx_slots(
		int count,
		const GUID* eax_ids);


	void set_obstruction_all(
		const EaxxEaxCall& eax_call);

	void set_occlusion_all(
		const EaxxEaxCall& eax_call);

	void set_room(
		const EaxxEaxCall& eax_call);

	void set_occlusion(
		const EaxxEaxCall& eax_call);

	void set_exclusion(
		const EaxxEaxCall& eax_call);

	void set_flags(
		const EaxxEaxCall& eax_call);

	void set_active_fx_slots(
		const EaxxEaxCall& eax_call);
}; // EaxxSource

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


} // eaxefx


#endif // !EAXEFX_EAXX_SOURCE_INCLUDED
