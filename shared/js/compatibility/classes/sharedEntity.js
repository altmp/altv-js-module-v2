export class SharedEntity {
    hasStreamSyncedMeta(key) {
        return this.streamSyncedMeta[key] !== undefined;
    }

    getStreamSyncedMeta(key) {
        return this.streamSyncedMeta[key];
    }

    getStreamSyncedMetaKeys() {
        return Object.keys(this.streamSyncedMeta);
    }
}
