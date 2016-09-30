import jnettool.tools.elements.NetworkElement
import jnettool.tools.Routing
import jnettool.tools.RouteInspector
import logging

class NetworkElement(object):
    'Adapter wrapper around the jnettools NetworkElement'

    def __init__(self, ipaddr):
        self.ipaddr = ipaddr
        self.oldne = jnettool.tools.elements.NetworkElement(ipaddr)

    @property
    def routing_table(self):
        return RoutingTable(self.oldne.getRoutingTable())

    def __enter__(self):
        return self

    def __exit__(self, exctype, excinst, exctb):
        handled = False
        if exctype == jnettool.tools.elements.MissingVar:
            logging.exception('No routing table found')
            self.ne.cleanup('rollback')
            handled = True
        elif exctype is None:
            self.ne.cleanup('commit')
        self.ne.disconnect()
        return handled

    def __repr__(self):
        return '%s(%r)' % (self.__class__.__name__, self.ipaddr)

class RoutingTable(object):
    'Adapter wrapper around the jnettools RoutingTable'

    def __init__(self, old_table):
        self.old_table = old_table

    def __len__(self):
        return self.old_table.getSize()

    def __getitem__(self, index):
        if index >= len(self):
            raise IndexError('Route offset out of range')
        return Route(self.old_table.getRouteByIndex(index))

class Route(object):

    def __init__(self, old_route):
        self.old_route = old_route

    @property
    def name(self):
        self.old_route.getName()

    @property
    def ipaddr(self):
        self.old_route.getIPAddr()


