const alt = __altModule;
alt.log("Bootstrapper loaded", alt.Resource.current.name);

try {
    __startResource();
} catch (err) {
    alt.logError("Error while starting resource", alt.Resource.current.name);
    alt.logError(err);
}
