export class SharedEntity {
    hasStreamSyncedMeta(key) {
        return key in this.streamSyncedMeta;
    }

    getStreamSyncedMeta(key) {
        return this.streamSyncedMeta[key];
    }

    getStreamSyncedMetaKeys() {
        return Object.keys(this.streamSyncedMeta);
    }
}
