function getDictionary() {
    return http.get('/dictionary.json')
        .then(function (result) {
            return result.data;
        });
}

var objectProvider = {
    get: function (identifier) {
        return getDictionary().then(function (dictionary) {
            if (identifier.key === 'spacecraft') {
                return {
                    identifier: identifier,
                    name: dictionary.name,
                    type: 'layout',
                    location: 'ROOT',
                    configuration : {
                        layout: {
                            panels: {
                                "example.taxonomy:prop.temp" : {
                                    "position": [0, 0],
                                    "dimensions": [19, 10]
                                },
                                "example.taxonomy:prop.hum": {
                                    "position": [19.5, 0],
                                    "dimensions": [19, 10]
                                },
                                "example.taxonomy:prop.pressure": {
                                    "position": [39, 0],
                                    "dimensions": [19, 10]
                                },
                                "example.taxonomy:prop.magx": {
                                    "position": [0, 10],
                                    "dimensions": [19, 10]
                                },
                                "example.taxonomy:prop.magy": {
                                    "position": [19.5, 10],
                                    "dimensions": [19, 10]
                                },
                                "example.taxonomy:prop.magz": {
                                    "position": [39, 10],
                                    "dimensions": [19, 10]
                                },
                                "example.taxonomy:prop.accx": {
                                    "position": [0, 20],
                                    "dimensions": [19, 10]
                                },
                                "example.taxonomy:prop.accy": {
                                    "position": [19.5, 20],
                                    "dimensions": [19, 10],
                                },
                                "example.taxonomy:prop.accz": {
                                    "position": [39, 20],
                                    "dimensions": [19, 10]
                                }
                            }
                        }
                }
                };
            } else {
                var measurement = dictionary.measurements.filter(function (m) {
                    return m.key === identifier.key;
                })[0];
                return {
                    identifier: identifier,
                    name: measurement.name,
                    type: 'example.telemetry',
                    telemetry: {
                        values: measurement.values
                    },
                    location: 'example.taxonomy:spacecraft'
                };
            }
        });
    }
};

var compositionProvider = {
    appliesTo: function (domainObject) {
        return domainObject.identifier.namespace === 'example.taxonomy' &&
               domainObject.type === 'layout';
    },
    load: function (domainObject) {
        return getDictionary()
            .then(function (dictionary) {
                return dictionary.measurements.map(function (m) {
                    return {
                        namespace: 'example.taxonomy',
                        key: m.key
                    };
                });
            });
    }
};

var DictionaryPlugin = function (openmct) {
    return function install(openmct) {
        openmct.objects.addRoot({
            namespace: 'example.taxonomy',
            key: 'spacecraft'
        });

        openmct.objects.addProvider('example.taxonomy', objectProvider);

        openmct.composition.addProvider(compositionProvider);


        openmct.types.addType('example.telemetry', {
            name: 'Example Telemetry Point',
            description: 'Example telemetry point from our happy tutorial.',
            cssClass: 'icon-telemetry'
        });
    };
};
