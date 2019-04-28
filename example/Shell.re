type state = {currentRoute: Routes.t};

type action =
  | SetRoute(Routes.t)
  | Open
  | Close;

let navTo = (route, event) => {
  ReactEvent.Mouse.preventDefault(event);
  Navigate.to_(route);
};

let navNav = (currentRoute, routeTo, name) => {
  let href = Navigate.pathFor(routeTo);
  let disabled = currentRoute === routeTo;
  let navTo = navTo(routeTo);
  let el =
    <Bootstrap.Nav.Link href disabled onClick=navTo>
      {React.string(name)}
    </Bootstrap.Nav.Link>;
  el;
};

let initialState = () => {
  currentRoute:
    ReasonReact.Router.dangerouslyGetInitialUrl() |> Router.urlHandler,
};

let reducer = (state, action): state => {
  switch (action) {
  | SetRoute(route) => {currentRoute: route}
  | _ => state
  };
};

[@react.component]
let make = () => {
  /*  didMount: self => {
        let watcherId =
          ReasonReact.Router.watchUrl(url => {
            let route = Router.urlHandler(url);
            self.send(SetRoute(route));
          });
        self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
      }, */

  let (state, dispatch) = React.useReducer(reducer, initialState());

  React.useEffect0(() => {
    let watcherId =
      ReasonReact.Router.watchUrl(url => {
        let route = Router.urlHandler(url);
        dispatch(SetRoute(route));
      });
    Some(() => ReasonReact.Router.unwatchUrl(watcherId));
  });

  let element = Router.elementForRoute(state.currentRoute);
  let navTo = navNav(state.currentRoute);
  <div>
    <Bootstrap.Navbar light=false color=Bootstrap.Colors.Background.Dark>
      <Bootstrap.Navbar.Brand>
        {React.string("Widget Play")}
      </Bootstrap.Navbar.Brand>
    </Bootstrap.Navbar>
    <Bootstrap.Layout.Container>
      <Bootstrap.Layout.Row>
        <Bootstrap.Layout.Col> element </Bootstrap.Layout.Col>
        <Bootstrap.Layout.Col
          md={Bootstrap.Layout.Col.shape(
            ~size=Bootstrap.Layout.ColSizes.Size(2),
            (),
          )}>
          <p> {React.string("Select Example")} </p>
          <Bootstrap.Nav vertical=true>
            <Bootstrap.Nav.Item>

                {navTo(Routes.BadgesExampleRoute, "Badges")}
                {navTo(Routes.BreadcrumbExampleRoute, "Breadcrumbs")}
                {navTo(Routes.ButtonExampleRoute, "Buttons")}
                {navTo(Routes.CollapseExampleRoute, "Collapse")}
                {navTo(Routes.DropdownExampleRoute, "Dropdown")}
                {navTo(Routes.FormExampleRoute, "Forms")}
                /*(navTo(Routes.ModalExampleRoute, "Modals")) */
                {navTo(Routes.PaginationExampleRoute, "Pagination")}
                   (navTo(Routes.ProgressExampleRoute, "Progress Bars")) 
                {navTo(Routes.TableExampleRoute, "Tables")}
                {navTo(Routes.TabExampleRoute, "Tabs")}
              </Bootstrap.Nav.Item>
              /* (navTo(Routes.AlertExampleRoute, "Alerts")) */
          </Bootstrap.Nav>
        </Bootstrap.Layout.Col>
      </Bootstrap.Layout.Row>
    </Bootstrap.Layout.Container>
  </div>;
};