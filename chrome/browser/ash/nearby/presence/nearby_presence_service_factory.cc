// Copyright 2023 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ash/nearby/presence/nearby_presence_service_factory.h"

#include <memory>

#include "base/memory/singleton.h"
#include "build/build_config.h"
#include "chrome/browser/ash/nearby/nearby_process_manager_factory.h"
#include "chrome/browser/ash/profiles/profile_helper.h"
#include "chrome/browser/browser_features.h"
#include "chrome/browser/profiles/profile.h"
#include "chromeos/ash/components/nearby/presence/nearby_presence_service_impl.h"
#include "chromeos/ash/components/nearby/presence/prefs/nearby_presence_prefs.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "components/user_manager/user_manager.h"
#include "content/public/browser/browser_context.h"

namespace {

constexpr char kServiceName[] = "NearbyPresenceService";

}  // namespace

namespace ash::nearby::presence {

// static
NearbyPresenceServiceFactory* NearbyPresenceServiceFactory::GetInstance() {
  return base::Singleton<NearbyPresenceServiceFactory>::get();
}

// static
NearbyPresenceService* NearbyPresenceServiceFactory::GetForBrowserContext(
    content::BrowserContext* context) {
  return static_cast<NearbyPresenceServiceImpl*>(
      GetInstance()->GetServiceForBrowserContext(context, /*create=*/true));
}

NearbyPresenceServiceFactory::NearbyPresenceServiceFactory()
    : ProfileKeyedServiceFactory(kServiceName) {
  DependsOn(ash::nearby::NearbyProcessManagerFactory::GetInstance());
}

NearbyPresenceServiceFactory::~NearbyPresenceServiceFactory() = default;

KeyedService* NearbyPresenceServiceFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  if (!context) {
    return nullptr;
  }

  Profile* profile = Profile::FromBrowserContext(context);
  if (!profile) {
    return nullptr;
  }

  // Nearby Presence is not supported for secondary profiles.
  if (!ProfileHelper::IsPrimaryProfile(profile)) {
    return nullptr;
  }

  // Guest/incognito profiles cannot use Nearby Presence.
  if (profile->IsOffTheRecord()) {
    return nullptr;
  }

  // Likewise, kiosk users are ineligible.
  if (user_manager::UserManager::Get()->IsLoggedInAsAnyKioskApp()) {
    return nullptr;
  }

  // TODO(b/276344576): add the NearbyPresence feature flag.

  VLOG(1) << __func__ << ": creating NearbyPresenceService.";
  return new NearbyPresenceServiceImpl(
      Profile::FromBrowserContext(context)->GetPrefs());
}

void NearbyPresenceServiceFactory::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  RegisterNearbyPresencePrefs(registry);
}

}  // namespace ash::nearby::presence
