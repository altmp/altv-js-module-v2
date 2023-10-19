#include "Class.h"
#include "interfaces/IAltResource.h"
#include "cpp-sdk/ICore.h"

static void ModelGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    ctx.Return(player->GetModel());
}

static void ModelSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t model;
    if(!ctx.GetValueAsHash(model)) return;

    player->SetModel(model);
}

static void CurrentWeaponGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    ctx.Return(player->GetCurrentWeapon());
}

static void CurrentWeaponSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetValueAsHash(weapon)) return;

    player->SetCurrentWeapon(weapon);
}

static void HeadBlendDataGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    alt::HeadBlendData headBlend = player->GetHeadBlendData();

    js::Object obj;
    obj.Set("shapeFirstID", headBlend.shapeFirstID);
    obj.Set("shapeSecondID", headBlend.shapeSecondID);
    obj.Set("shapeThirdID", headBlend.shapeThirdID);
    obj.Set("skinFirstID", headBlend.skinFirstID);
    obj.Set("skinSecondID", headBlend.skinSecondID);
    obj.Set("skinThirdID", headBlend.skinThirdID);
    obj.Set("shapeMix", headBlend.shapeMix);
    obj.Set("skinMix", headBlend.skinMix);
    obj.Set("thirdMix", headBlend.thirdMix);
    ctx.Return(obj);
}

static void HeadBlendDataSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    js::Object data;
    if(!ctx.GetValue(data)) return;

    uint32_t shapeFirstID = data.Get<uint32_t>("shapeFirstID");
    uint32_t shapeSecondID = data.Get<uint32_t>("shapeSecondID");
    uint32_t shapeThirdID = data.Get<uint32_t>("shapeThirdID");
    uint32_t skinFirstID = data.Get<uint32_t>("skinFirstID");
    uint32_t skinSecondID = data.Get<uint32_t>("skinSecondID");
    uint32_t skinThirdID = data.Get<uint32_t>("skinThirdID");
    float shapeMix = data.Get<float>("shapeMix");
    float skinMix = data.Get<float>("skinMix");
    float thirdMix = data.Get<float>("thirdMix");

    player->SetHeadBlendData(shapeFirstID, shapeSecondID, shapeThirdID, skinFirstID, skinSecondID, skinThirdID, shapeMix, skinMix, thirdMix);
}

static void EyeColorGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();
    ctx.Return(player->GetEyeColor());
}

static void EyeColorSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    int16_t color;
    if(!ctx.GetValue(color)) return;

    ctx.Return(player->SetEyeColor(color));
}

static void WeaponsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    std::vector<alt::Weapon> weapons = player->GetWeapons();
    js::Array arr(weapons.size());
    for(auto weapon : weapons)
    {
        js::Object obj;
        obj.Set("hash", weapon.hash);
        obj.Set("tintIndex", weapon.tintIndex);
        js::Array components(weapon.components.size());
        for(auto component : weapon.components)
        {
            components.Push(component);
        }
        obj.Set("components", components);
        arr.Push(obj);
    }

    ctx.Return(arr);
}

static void SendNamesGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    ctx.Return(player->GetSendNames());
}

static void SendNamesSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    bool state;
    if(!ctx.GetValue(state)) return;

    player->SetSendNames(state);
}

static void StreamedEntitiesGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    auto isolate = ctx.GetIsolate();
    auto _ctx = ctx.GetContext();

    const std::vector<std::pair<alt::IEntity*, int32_t>> list = player->GetStreamedEntities();
    js::Array streamedInEntities(list.size());

    for(auto& [entity, distance] : list)
    {
        js::Object entityObj;

        entityObj.Set("entity", entity);
        entityObj.Set("distance", distance);

        streamedInEntities.Push(entityObj);
    }

    ctx.Return(streamedInEntities);
}

static void Emit(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1, 32)) return;
    js::IResource* resource = ctx.GetResource();

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    std::string eventName;
    if(!ctx.GetArg(0, eventName)) return;

    alt::MValueArgs args;
    args.reserve(ctx.GetArgCount() - 1);
    alt::MValue val;
    for(int i = 1; i < ctx.GetArgCount(); i++)
    {
        if(resource->IsRawEmitEnabled())
        {
            v8::Local<v8::Value> arg;
            if(!ctx.GetArg(i, arg)) continue;
            alt::MValueByteArray result = js::JSToRawBytes(arg, resource);
            if(!ctx.Check(result.get() != nullptr, "Failed to serialize argument at index " + std::to_string(i - 1))) return;
            val = result;
        }
        else if(!ctx.GetArg(i, val))
            continue;

        args.push_back(val);
    }
    alt::ICore::Instance().TriggerClientEvent(player, eventName, args);
}

static void EmitUnreliable(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1, 32)) return;
    js::IResource* resource = ctx.GetResource();

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    std::string eventName;
    if(!ctx.GetArg(0, eventName)) return;

    alt::MValueArgs args;
    args.reserve(ctx.GetArgCount() - 1);
    alt::MValue val;
    for(int i = 1; i < ctx.GetArgCount(); i++)
    {
        if(resource->IsRawEmitEnabled())
        {
            v8::Local<v8::Value> arg;
            if(!ctx.GetArg(i, arg)) continue;
            alt::MValueByteArray result = js::JSToRawBytes(arg, resource);
            if(!ctx.Check(result.get() != nullptr, "Failed to serialize argument at index " + std::to_string(i - 1))) return;
            val = result;
        }
        else if(!ctx.GetArg(i, val))
            continue;

        args.push_back(val);
    }
    alt::ICore::Instance().TriggerClientEventUnreliable(player, eventName, args);
}

static void Spawn(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1, 2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    alt::Vector3f pos;
    if(!ctx.GetArg(0, pos)) return;

    uint32_t delay = ctx.GetArg<uint32_t>(1);

    player->Spawn(pos, delay);
}

static void SetWeaponTintIndex(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    uint8_t tintIndex;
    if(!ctx.GetArg(1, tintIndex)) return;

    player->SetWeaponTintIndex(weapon, tintIndex);
}

static void AddWeaponComponent(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    uint32_t component;
    if(!ctx.GetArgAsHash(1, component)) return;

    player->AddWeaponComponent(weapon, component);
}

static void RemoveWeaponComponent(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    uint32_t component;
    if(!ctx.GetArgAsHash(1, component)) return;

    player->RemoveWeaponComponent(weapon, component);
}

static void GiveWeapon(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2, 3)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    uint16_t ammo;
    if(!ctx.GetArg(1, ammo)) return;

    bool selectWeapon = false;
    if(ctx.GetArgCount() == 3)
    {
        if(!ctx.GetArg(2, selectWeapon)) return;
    }

    player->GiveWeapon(weapon, ammo, selectWeapon);
}

static void RemoveWeapon(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    player->RemoveWeapon(weapon);
}

static void RemoveAllWeapons(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    bool removeAmmo = ctx.GetArg<bool>(0, true);

    player->RemoveAllWeapons(removeAmmo);
}

static void GetClothes(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint8_t component;
    if(!ctx.GetArg(0, component)) return;

    alt::Cloth cloth = player->GetClothes(component);
    js::Object obj;
    obj.Set("drawable", cloth.drawableId);
    obj.Set("texture", cloth.textureId);
    obj.Set("palette", cloth.paletteId);
    ctx.Return(obj);
}

static void GetDlcClothes(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint8_t component;
    if(!ctx.GetArg(0, component)) return;

    alt::DlcCloth cloth = player->GetDlcClothes(component);
    js::Object obj;
    obj.Set("dlc", cloth.dlc);
    obj.Set("drawable", cloth.drawableId);
    obj.Set("texture", cloth.textureId);
    obj.Set("palette", cloth.paletteId);
    ctx.Return(obj);
}

static void GetProp(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint8_t component;
    if(!ctx.GetArg(0, component)) return;

    alt::Prop prop = player->GetProps(component);
    js::Object obj;
    obj.Set("drawable", prop.drawableId);
    obj.Set("texture", prop.textureId);
    ctx.Return(obj);
}

static void GetDlcProps(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint8_t component;
    if(!ctx.GetArg(0, component)) return;

    alt::DlcProp prop = player->GetDlcProps(component);
    js::Object obj;
    obj.Set("dlc", prop.dlc);
    obj.Set("drawable", prop.drawableId);
    obj.Set("texture", prop.textureId);
    ctx.Return(obj);
}

static void IsEntityInStreamingRange(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgType(0, { js::Type::BASE_OBJECT, js::Type::NUMBER })) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t entityId = 0;
    if(ctx.GetArgType(0) == js::Type::BASE_OBJECT)
    {
        alt::IBaseObject* object;
        if(!ctx.GetArg(0, object)) return;
        entityId = object->GetID();
    }
    else
    {
        uint32_t id;
        if(!ctx.GetArg(0, id)) return;
        entityId = id;
    }

    ctx.Return(player->IsEntityInStreamingRange(entityId));
}

static void GetHeadOverlay(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint8_t overlay;
    if(!ctx.GetArg(0, overlay)) return;

    alt::HeadOverlay headOverlay = player->GetHeadOverlay(overlay);
    js::Object obj;
    obj.Set("index", headOverlay.index);
    obj.Set("opacity", headOverlay.opacity);
    obj.Set("colorType", headOverlay.colorType);
    obj.Set("colorIndex", headOverlay.colorIndex);
    obj.Set("secondColorIndex", headOverlay.secondColorIndex);
    ctx.Return(obj);
}

static void SetHeadBlendPaletteColor(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2, 4)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint8_t id;
    if(!ctx.GetArg(0, id)) return;

    alt::RGBA color;
    if(ctx.GetArgCount() == 2)
    {
        if(!ctx.GetArg(1, color)) return;
    }
    else
    {
        uint8_t r, g, b;
        if(!ctx.GetArg(1, r)) return;
        if(!ctx.GetArg(2, g)) return;
        if(!ctx.GetArg(3, b)) return;
        color = alt::RGBA{ r, g, b, 0 };
    }
    player->SetHeadBlendPaletteColor(id, color.r, color.g, color.b);
}

static void PlayAnimation(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2, 10)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    std::string animDict;
    if(!ctx.GetArg(0, animDict)) return;
    std::string animName;
    if(!ctx.GetArg(1, animName)) return;

    float blendInSpeed = ctx.GetArg(2, 8.0f);
    float blendOutSpeed = ctx.GetArg(3, 8.0f);
    int32_t duration = ctx.GetArg(4, -1);
    uint32_t flag = ctx.GetArg(5, 0);
    float playbackRate = ctx.GetArg(6, 1.0f);
    bool lockX = ctx.GetArg(7, false);
    bool lockY = ctx.GetArg(8, false);
    bool lockZ = ctx.GetArg(9, false);

    player->PlayAnimation(animDict, animName, blendInSpeed, blendOutSpeed, duration, flag, playbackRate, lockX, lockY, lockZ);
}

static void HasWeapon(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    ctx.Return(player->HasWeapon(weapon));
}

static void GetAmmo(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    ctx.Return(player->GetAmmo(ammoHash));
}

static void SetAmmo(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    uint16_t ammoCount;
    if(!ctx.GetArg(1, ammoCount)) return;

    player->SetAmmo(ammoHash, ammoCount);
}

static void GetWeaponAmmo(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weaponHash;
    if(!ctx.GetArgAsHash(0, weaponHash)) return;

    ctx.Return(player->GetWeaponAmmo(weaponHash));
}

static void SetWeaponAmmo(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weaponHash;
    if(!ctx.GetArgAsHash(0, weaponHash)) return;

    uint16_t ammoCount;
    if(!ctx.GetArg(1, ammoCount)) return;

    player->SetWeaponAmmo(weaponHash, ammoCount);
}

static void GetAmmoSpecialType(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    ctx.Return(player->GetAmmoSpecialType(ammoHash));
}

static void SetAmmoSpecialType(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    alt::AmmoSpecialType ammoSpecialType;
    if(!ctx.GetArg(1, ammoSpecialType)) return;

    player->SetAmmoSpecialType(ammoHash, ammoSpecialType);
}

static void GetAmmoFlags(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    alt::AmmoFlags flags = player->GetAmmoFlags(ammoHash);

    js::Object obj;
    obj.Set("ammoHash", ammoHash);
    obj.Set("infiniteAmmo", flags.infiniteAmmo);
    obj.Set("addSmokeOnExplosion", flags.addSmokeOnExplosion);
    obj.Set("fuse", flags.fuse);
    obj.Set("fixedAfterExplosion", flags.fixedAfterExplosion);

    ctx.Return(obj);
}

static void SetAmmoFlags(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    js::Object data;
    if(!ctx.GetArg(0, data)) return;

    uint32_t ammoHash;
    if(!data.GetAsHash("ammoHash", ammoHash)) return;

    bool infiniteAmmo;
    if(!data.Get("infiniteAmmo", infiniteAmmo)) return;

    bool addSmokeOnExplosion;
    if(!data.Get("addSmokeOnExplosion", addSmokeOnExplosion)) return;

    bool fuse;
    if(!data.Get("fuse", fuse)) return;

    bool fixedAfterExplosion;
    if(!data.Get("fixedAfterExplosion", fixedAfterExplosion)) return;

    player->SetAmmoFlags(ammoHash, alt::AmmoFlags{ infiniteAmmo, addSmokeOnExplosion, fuse, fixedAfterExplosion });
}

static void GetAmmoMax(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    ctx.Return(player->GetAmmoMax(ammoHash));
}

static void SetAmmoMax(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    int32_t ammoMax;
    if(!ctx.GetArg(1, ammoMax)) return;

    player->SetAmmoMax(ammoHash, ammoMax);
}

static void GetAmmoMax50(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    ctx.Return(player->GetAmmoMax50(ammoHash));
}

static void SetAmmoMax50(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    int32_t ammoMax;
    if(!ctx.GetArg(1, ammoMax)) return;

    player->SetAmmoMax50(ammoHash, ammoMax);
}

static void GetAmmoMax100(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    ctx.Return(player->GetAmmoMax100(ammoHash));
}

static void SetAmmoMax100(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t ammoHash;
    if(!ctx.GetArgAsHash(0, ammoHash)) return;

    int32_t ammoMax;
    if(!ctx.GetArg(1, ammoMax)) return;

    player->SetAmmoMax100(ammoHash, ammoMax);
}

static void AddDecoration(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t collection;
    if(!ctx.GetArgAsHash(0, collection)) return;

    uint32_t overlay;
    if(!ctx.GetArgAsHash(1, overlay)) return;

    player->AddDecoration(collection, overlay);
}

static void RemoveDecoration(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t collection;
    if(!ctx.GetArgAsHash(0, collection)) return;

    uint32_t overlay;
    if(!ctx.GetArgAsHash(1, overlay)) return;

    player->RemoveDecoration(collection, overlay);
}

static void GetDecorations(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    std::vector<alt::CDecoration> decorations = player->GetDecorations();
    js::Array arr(decorations.size());
    for(auto decoration : decorations)
    {
        js::Object obj;
        obj.Set("collection", decoration.collection);
        obj.Set("overlay", decoration.overlay);
        arr.Push(obj);
    }

    ctx.Return(arr);
}

static void LocalMetaGetter(js::DynamicPropertyGetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IPlayer* player = ctx.GetParent<alt::IPlayer>();

    ctx.Return(player->GetLocalMetaData(ctx.GetProperty()));
}

static void LocalMetaSetter(js::DynamicPropertySetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IPlayer* player = ctx.GetParent<alt::IPlayer>();

    alt::MValue value;
    if(!ctx.GetValue(value)) return;

    player->SetLocalMetaData(ctx.GetProperty(), value);
}

static void LocalMetaDeleter(js::DynamicPropertyDeleterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IPlayer* player = ctx.GetParent<alt::IPlayer>();

    if(!player->HasLocalMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    player->DeleteLocalMetaData(ctx.GetProperty());
    ctx.Return(true);
}

static void LocalMetaEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IPlayer* player = ctx.GetParent<alt::IPlayer>();

    ctx.Return(player->GetLocalMetaDataKeys());
}

// clang-format off
extern js::Class sharedPlayerClass;
extern js::Class playerClass("Player", &sharedPlayerClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PLAYER);

    tpl.LazyProperty<&alt::IPlayer::GetIP>("ip");
    tpl.LazyProperty<&alt::IPlayer::GetSocialID>("socialID");
    tpl.LazyProperty<&alt::IPlayer::GetSocialClubName>("socialClubName");
    tpl.LazyProperty<&alt::IPlayer::GetHwidHash>("hwidHash");
    tpl.LazyProperty<&alt::IPlayer::GetHwidExHash>("hwidExHash");
    tpl.LazyProperty<&alt::IPlayer::GetCloudID>("cloudID");
    tpl.LazyProperty<&alt::IPlayer::GetCloudAuthResult>("cloudAuthResult");

    tpl.Property<&alt::IPlayer::IsConnected>("isConnected");
    tpl.Property<&alt::IPlayer::GetPing>("ping");
    tpl.Property<&alt::IPlayer::GetAuthToken>("authToken");
    tpl.Property<&alt::IPlayer::GetDiscordId>("discordID");
    tpl.Property("model", &ModelGetter, &ModelSetter);
    tpl.Property<&alt::IPlayer::GetArmour, &alt::IPlayer::SetArmour>("armour");
    tpl.Property<&alt::IPlayer::GetMaxArmour, &alt::IPlayer::SetMaxArmour>("maxArmour");
    tpl.Property("currentWeapon", &CurrentWeaponGetter, &CurrentWeaponSetter);
    tpl.Property<&alt::IPlayer::GetHealth, &alt::IPlayer::SetHealth>("health");
    tpl.Property<&alt::IPlayer::GetMaxHealth, &alt::IPlayer::SetMaxHealth>("maxHealth");
    tpl.Property<&alt::IPlayer::GetInvincible, &alt::IPlayer::SetInvincible>("invincible");
    tpl.Property("headBlendData", &HeadBlendDataGetter, &HeadBlendDataSetter);
    tpl.Property("eyeColor", &EyeColorGetter, &EyeColorSetter);
    tpl.Property<&alt::IPlayer::GetHairColor, &alt::IPlayer::SetHairColor>("hairColor");
    tpl.Property<&alt::IPlayer::GetHairHighlightColor, &alt::IPlayer::SetHairHighlightColor>("hairHighlightColor");
    tpl.Property("weapons", &WeaponsGetter);
    tpl.Property<&alt::IPlayer::GetInteriorLocation>("interiorLocation");
    tpl.Property<&alt::IPlayer::GetLastDamagedBodyPart>("lastDamagedBodyPart");
    tpl.Property("sendNames", &SendNamesGetter, &SendNamesSetter);
    tpl.Property("streamedEntities", StreamedEntitiesGetter);
    tpl.Property<&alt::IPlayer::IsNetworkOwnershipDisabled, &alt::IPlayer::SetNetworkOwnershipDisabled>("netOwnershipDisabled");
    tpl.Property<&alt::IPlayer::GetBloodDamageBase64, &alt::IPlayer::SetBloodDamageBase64>("bloodDamageBase64");

    tpl.Method("emit", &Emit);
    tpl.Method("emitUnreliable", &EmitUnreliable);
    tpl.Method("spawn", &Spawn);
    tpl.Method<&alt::IPlayer::Despawn>("despawn");
    tpl.Method("setWeaponTintIndex", &SetWeaponTintIndex);
    tpl.Method("addWeaponComponent", &AddWeaponComponent);
    tpl.Method("removeWeaponComponent", &RemoveWeaponComponent);
    tpl.Method<&alt::IPlayer::ClearBloodDamage>("clearBloodDamage");
    tpl.Method("giveWeapon", &GiveWeapon);
    tpl.Method("removeWeapon", &RemoveWeapon);
    tpl.Method("removeAllWeapons", RemoveAllWeapons);
    tpl.Method<&alt::IPlayer::SetDateTime>("setDateTime");
    tpl.Method<&alt::IPlayer::SetWeather>("setWeather");
    tpl.Method<&alt::IPlayer::Kick>("kick");
    tpl.Method("getClothes", &GetClothes);
    tpl.Method<&alt::IPlayer::SetClothes>("setClothes");
    tpl.Method("getDlcClothes", &GetDlcClothes);
    tpl.Method<&alt::IPlayer::SetDlcClothes>("setDlcClothes");
    tpl.Method("getProp", &GetProp);
    tpl.Method<&alt::IPlayer::SetProps>("setProp");
    tpl.Method("getDlcProp", &GetDlcProps);
    tpl.Method<&alt::IPlayer::SetDlcProps>("setDlcProp");
    tpl.Method<&alt::IPlayer::ClearProps>("clearProp");
    tpl.Method("isEntityInStreamingRange", &IsEntityInStreamingRange);
    tpl.Method<&alt::IPlayer::SetIntoVehicle>("setIntoVehicle");
    tpl.Method<&alt::IPlayer::PlayAmbientSpeech>("playAmbientSpeech");
    tpl.Method<&alt::IPlayer::SetHeadOverlay>("setHeadOverlay");
    tpl.Method<&alt::IPlayer::RemoveHeadOverlay>("removeHeadOverlay");
    tpl.Method<&alt::IPlayer::SetHeadOverlayColor>("setHeadOverlayColor");
    tpl.Method("getHeadOverlay", &GetHeadOverlay);
    tpl.Method<&alt::IPlayer::SetFaceFeature>("setFaceFeature");
    tpl.Method<&alt::IPlayer::GetFaceFeatureScale>("getFaceFeature");
    tpl.Method<&alt::IPlayer::RemoveFaceFeature>("removeFaceFeature");
    tpl.Method("setHeadBlendPaletteColor", &SetHeadBlendPaletteColor);
    tpl.Method<&alt::IPlayer::GetHeadBlendPaletteColor>("getHeadBlendPaletteColor");
    tpl.Method("playAnimation", &PlayAnimation);
    tpl.Method<&alt::IPlayer::ClearTasks>("clearTasks");
    tpl.Method("hasWeapon", HasWeapon);
    tpl.Method("getAmmo", GetAmmo);
    tpl.Method("setAmmo", SetAmmo);
    tpl.Method("getWeaponAmmo", GetWeaponAmmo);
    tpl.Method("setWeaponAmmo", SetWeaponAmmo);
    tpl.Method("getAmmoSpecialType", GetAmmoSpecialType);
    tpl.Method("setAmmoSpecialType", SetAmmoSpecialType);
    tpl.Method("getAmmoFlags", GetAmmoFlags);
    tpl.Method("setAmmoFlags", SetAmmoFlags);
    tpl.Method("getAmmoMax", GetAmmoMax);
    tpl.Method("setAmmoMax", SetAmmoMax);
    tpl.Method("getAmmoMax50", GetAmmoMax50);
    tpl.Method("setAmmoMax50", SetAmmoMax50);
    tpl.Method("getAmmoMax100", GetAmmoMax100);
    tpl.Method("setAmmoMax100", SetAmmoMax100);
    tpl.Method("addDecoration", AddDecoration);
    tpl.Method("removeDecoration", RemoveDecoration);
    tpl.Method<&alt::IPlayer::ClearDecorations>("clearDecorations");
    tpl.Method("getDecorations", GetDecorations);
    tpl.Method<&alt::IPlayer::PlayScenario>("playScenario");

    tpl.DynamicProperty("localMeta", LocalMetaGetter, LocalMetaSetter, LocalMetaDeleter, LocalMetaEnumerator);

    tpl.GetByID<alt::IBaseObject::Type::PLAYER>();
});
